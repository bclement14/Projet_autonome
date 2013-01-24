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

	cout << "Getting results in" << fileName << " during 7.5 sec" << endl;

	bool timeOut = false; int loop = 0;
	ofstream fichier(fileName.c_str(), ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert

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
	    cout << loop << "/250 " << endl; 
	    fichier << loop << " ";
	    valeur = (*motors)["GEpauleLong"]->getCurrentAngle(); //Epaule longitudinale (1er moteur)
	    //cout << "GEpauleLong : " << valeur << endl; 
	    fichier << valeur << " ";
	    valeur = (*motors)["GEpauleLat"]->getCurrentAngle(); //Epaule laterale
	    fichier << valeur << " ";
	    valeur = (*motors)["GEpauleRot"]->getCurrentAngle();
	    //cout << "GEpauleRot : " << valeur << endl; 
	    fichier << valeur << " ";
	    valeur = (*motors)["GCoude"]->getCurrentAngle();
	    //cout << "GCoude : " << valeur << endl; 
	    fichier << valeur << " ";
	    valeur = (*motors)["GCoudeRot"]->getCurrentAngle();
	    fichier << valeur << " ";
	    valeur = (*motors)["GPoignetLong"]->getCurrentAngle();
	    fichier << valeur << " ";
	    valeur = (*motors)["GPoignetLat"]->getCurrentAngle();
	    //cout << "GPoignetLat : " << valeur << endl; 
	    fichier << valeur << endl;
	    syst_wait_ms(30);
	    loop++;
	    if (loop > 250)
	      timeOut = true;
	  }
	fichier.close();
	
	cout << "Putting all motors compliant " << endl;
	robot->allCompliant();
	syst_wait_ms(1000);

	cout << "Bye bye" << endl;
	robots.stop();
	}
	catch(string exc)
	{
		cout << "Received exception " << exc << endl;
		exit(0);
	}

}
