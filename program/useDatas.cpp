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
	
	cout << "Putting all motors compliant " << endl;
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
