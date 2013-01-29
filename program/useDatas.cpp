/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <main/Command.h>

#include <ticks.h>

#include <rhoban/robot/Robots.h>

using namespace std;
using namespace Rhoban;

void ssFirstPos(Motors * motors, const string &motorName, const double initPos, const double goalPos, const int pourcentage);
void goToFirstPos(Motors * motors, double posEpauleLong, double posEpauleLat, double posEpauleRot, 
		  double coude, double coudeRot, double poignetLong, double poignetLat, 
		  const double duration);
int main(int argc, char **argv)
{
  try
    {
      string fileName = "angleValues.txt";
      Robots robots;

	cout << "Coucou ! Starting " << endl;

	// Charge la configuration et connecte les robots
	robots.loadYaml("config.yml");

	Robot * robot = robots["drawer"];
	Motors * motors = robot->getMotors();
	Moves * moves = robot->getMoves();

	cout << "Starting motors " << endl;
	motors->start(30);
	syst_wait_ms(1000);

	cout << "Putting all motors compliant " << endl;
	robot->allCompliant();
	syst_wait_ms(1000);

	cout << "Now motors are going to their initial position " << endl;
	motors->goToInit();
	//robot->motors["GEpauleLong"].setLoad(1.0);

	cout << "Applying results from " << fileName << " during 7.5 sec" << endl;

	bool timeOut = false; int loop = 0;
	ifstream fichier(fileName.c_str(), ios::in);  // ouverture en lecture

	if(!fichier)
	  {
	    cout << "Opening file " << fileName << " failure. Stopping !";
	    robot->allCompliant();
	    robots.stop();
	    return 1;
	  }
	//On lit les premieres valeurs pour initialiser le moteur
	cout << "Now motors are going to position 1 of file" << endl;
	fichier >> loop;
	double posEpauleLong, posEpauleLat, posEpauleRot, posCoude, posCoudeRot, posPoignetLong, posPoignetLat;
	fichier >> posEpauleLong >> posEpauleLat >> posEpauleRot >> posCoude >> posCoudeRot >> posPoignetLong >> posPoignetLat;
	syst_wait_ms(3000);
	goToFirstPos(motors, posEpauleLong, posEpauleLat, posEpauleRot, posCoude, posCoudeRot, posPoignetLong, posPoignetLat,5);

	cout << "Reading sequence" << endl;
	timeOut = false;
	double valeur = 0;
	while (!timeOut)
	  {
	    fichier >> loop;
	    cout << loop << "/250 " << endl;
	    fichier >> valeur; 
	    cout << "GEpauleLong : " << valeur << endl;
	    (*motors)["GEpauleLong"]->setGoalAngle(valeur);
	    fichier >> valeur;
	    (*motors)["GEpauleLat"]->setGoalAngle(valeur);
	    fichier >> valeur;
	    (*motors)["GEpauleRot"]->setGoalAngle(valeur);
	    fichier >> valeur;
	    cout << "GCoude : " << valeur << endl; 
	    (*motors)["GCoude"]->setGoalAngle(valeur);
	    fichier >> valeur;
	    (*motors)["GCoudeRot"]->setGoalAngle(valeur);
	    fichier >> valeur;
	    (*motors)["GPoignetLong"]->setGoalAngle(valeur);
	    fichier >> valeur;
	    (*motors)["GPoignetLat"]->setGoalAngle(valeur); 
	    syst_wait_ms(30);
	    loop++;
	    if (loop > 250)
	      timeOut = true;
	      }
	      fichier.close();
	
	cout << "End of movement. Putting all motors compliant " << endl;
	robot->allCompliant();
	syst_wait_ms(1000);
	//robot->emergency();

	cout << "Bye bye" << endl;
	robots.stop();
	}
	catch(string exc)
	{
		cout << "Received exception " << exc << endl;
		exit(0);
	}

}

void goToFirstPos(Motors * motors, double posEpauleLong, double posEpauleLat, double posEpauleRot, 
		  double posCoude, double posCoudeRot, double posPoignetLong, double posPoignetLat, 
		  const double duration)
{
  double initEpauleLong = (*motors)["GEpauleLong"]->getCurrentAngle(),
    initEpauleLat = (*motors)["GEpauleLat"]->getCurrentAngle(),
    initEpauleRot = (*motors)["GEpauleRot"]->getCurrentAngle(),
    initCoude = (*motors)["GCoude"]->getCurrentAngle(), 
    initCoudeRot = (*motors)["GCoudeRot"]->getCurrentAngle(),
    initPoignetLong = (*motors)["GPoignetLong"]->getCurrentAngle(),
    initPoignetLat = (*motors)["GPoignetLat"]->getCurrentAngle();
  for (int i=1; i<=100; i++)
    {
      //EpauleLong
      ssFirstPos(motors, "GEpauleLong", initEpauleLong, posEpauleLong, i);
      //EpauleLat
      ssFirstPos(motors, "GEpauleLat", initEpauleLat, posEpauleLat, i);
      //EpauleRot
      ssFirstPos(motors, "GEpauleRot", initEpauleRot, posEpauleRot, i);
      //Coude
      ssFirstPos(motors, "GCoude", initCoude, posCoude, i);
      //CoudeRot
      ssFirstPos(motors, "GCoudeRot", initCoudeRot, posCoudeRot, i);
      //PoignetLong
      ssFirstPos(motors, "GPoignetLong", initPoignetLong, posPoignetLong, i);
      //PoignetLat
      ssFirstPos(motors, "GPoignetLat", initPoignetLat, posPoignetLat, i);
      syst_wait_ms(30);
    }
}

void ssFirstPos(Motors * motors, const string &motorName, const double initPos, const double goalPos, const int pourcentage)
{
  /*bool posOk = true;
  double valeur = (*motors)[motorName.c_str()]->getCurrentAngle();
  cout << motorName.c_str() << " : currentAngle = " << valeur << " goal = " << posMotor << " ";
  if (valeur-posMotor>1)
    {
      posOk = false;
      (*motors)[motorName.c_str()]->setGoalAngle(valeur-1);
      cout << motorName.c_str() << " : pos--" << endl;
    }
  else if (valeur-posMotor<-1)
    {
      posOk = false;
      (*motors)[motorName.c_str()]->setGoalAngle(valeur+1);
      cout << motorName.c_str() << " : pos++" << endl;
    }
  else
    (*motors)[motorName.c_str()]->setGoalAngle(posMotor);
    return posOk;*/
  double currentPos = (initPos*(100-pourcentage) + goalPos*pourcentage) / 100;
  cout << motorName.c_str() << " : currentPos = " << currentPos << " goal = " << goalPos << " ";
  (*motors)[motorName.c_str()]->setGoalAngle(currentPos);
}
