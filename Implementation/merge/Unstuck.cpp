#include "main.h"

Unstuck::Unstuck () {

	waitTime = 2.0;      //Number of Seconds to Wait Between Checks
	errorMargin = 2.0;   //Distance rover can travel and still be stuck
}

void Unstuck::getUnstuck () {

	float oldXCoord = 100.0;   //Previous X Coordinate
	float oldYCoord = 200.0;   //Previous Y Coordinate
	bool isStuck = true;       //Set to False Once Unstuck
	GPSFuncs myGPS;            //GPS Functions
	MotorFuncs myMotor;        //Motor Functions
	
	printf ("Testing Getting Unstuck from Obstacles Module:\n");
	printf ("X Coordinate: %f\nY Coordinate: %f\nWait Time: %f\n",
		oldXCoord, oldYCoord, waitTime);
	
	while (isStuck) {
		oldXCoord = myGPS.getXCoord (oldXCoord);
		oldYCoord = myGPS.getYCoord (oldYCoord);

		myMotor.roverBackward ();
		sleep (waitTime);
		myMotor.roverStop ();

		if (!checkStuck (oldXCoord, oldYCoord, myGPS)) {
			isStuck = false;
		}
		else {
			myMotor.roverRotate (45.0);
			sleep (waitTime);
		}
	}

	printf ("Successfully got Unstuck\n");
	printf ("Final X Coordinate: %f\nFinal Y Coordinate: %f\n",
		oldXCoord, oldYCoord);
}

//Returns True if Rover is Stuck.
bool Unstuck::checkStuck (float oldXCoord, float oldYCoord, GPSFuncs myGPS) {

	bool isStuck = false;     //Set to True if Rover is Stuck

	//Compute distance formula from current and previous coordinates
	if (sqrt (pow (myGPS.getXCoord (oldXCoord) - oldXCoord, 2) +
		  pow (myGPS.getYCoord (oldYCoord) - oldYCoord, 2)) < errorMargin)  {

		isStuck = true;
	}
	printf ("Rover is Stuck: %d\n", isStuck);
	return isStuck;
}
