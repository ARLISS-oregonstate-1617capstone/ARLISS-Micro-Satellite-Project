#include "main.h"

Unstuck::Unstuck (GPSFuncs* g, MotorFuncs* m) {

	waitTime = 2.0;      //Number of Seconds to Wait Between Checks
	errorMargin = 2.0;   //Distance rover can travel and still be stuck

	myGPS = g;
	myMotors = m;
}

void Unstuck::getUnstuck () {

	float oldXCoord = 0.;   //Previous X Coordinate
	float oldYCoord = 0.;   //Previous Y Coordinate
	bool isStuck = true;       //Set to False Once Unstuck

	oldXCoord = myGPS->getXCoord ();
	oldYCoord = myGPS->getYCoord ();
	
	printf ("Testing Getting Unstuck from Obstacles Module:\n");
	printf ("X Coordinate: %f\nY Coordinate: %f\nWait Time: %f\n",
		oldXCoord, oldYCoord, waitTime);
	
	while (isStuck) {
		oldXCoord = myGPS->getXCoord ();
		oldYCoord = myGPS->getYCoord ();

		myMotors->roverBackward ();
		sleep (waitTime);
		myMotors->roverStop ();

		if (!checkStuck (oldXCoord, oldYCoord)) {
			isStuck = false;
		}
		else {
			myMotors->roverRotate (45.0);
			sleep (waitTime);
		}
	}

	oldXCoord = myGPS->getXCoord ();
	oldYCoord = myGPS->getYCoord ();
	
	printf ("Successfully got Unstuck\n");
	printf ("Final X Coordinate: %f\nFinal Y Coordinate: %f\n",
		oldXCoord, oldYCoord);
}

//Returns True if Rover is Stuck.
bool Unstuck::checkStuck (float oldXCoord, float oldYCoord) {

	bool isStuck = false;     //Set to True if Rover is Stuck

	//Compute distance formula from current and previous coordinates
	if (sqrt (pow (myGPS->getXCoord () - oldXCoord, 2) +
		  pow (myGPS->getYCoord () - oldYCoord, 2)) < errorMargin)  {

		isStuck = true;
	}
	printf ("Rover is Stuck: %d\n", isStuck);
	return isStuck;
}
