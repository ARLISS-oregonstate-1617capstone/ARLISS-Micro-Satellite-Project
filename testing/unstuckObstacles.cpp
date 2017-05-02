#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void getUnstuck ();
bool checkStuck (float, float);

//GPS Functions
float getXCoord (float);
float getYCoord (float);

//Motor Functions
void roverRotate (float);
void roverForward ();
void roverBackward ();
void roverStop ();

int main () {

	getUnstuck ();
	
	return 0;
}

void getUnstuck () {

	float waitTime = 2.0;      //Number of Seconds to Wait Between Checks
	float oldXCoord = 100.0;   //Previous X Coordinate
	float oldYCoord = 200.0;   //Previous Y Coordinate
	bool isStuck = true;       //Set to False Once Unstuck
	
	printf ("Testing Getting Unstuck from Obstacles Module:\n");
	printf ("X Coordinate: %f\nY Coordinate: %f\nWait Time: %f\n",
		oldXCoord, oldYCoord, waitTime);
	
	while (isStuck) {
		oldXCoord = getXCoord (oldXCoord);
		oldYCoord = getYCoord (oldYCoord);

		roverBackward ();
		sleep (waitTime);
		roverStop ();

		if (!checkStuck (oldXCoord, oldYCoord)) {
			isStuck = false;
		}
		else {
			roverRotate (45.0);
			sleep (waitTime);
		}
	}

	printf ("Successfully got Unstuck\n");
	printf ("Final X Coordinate: %f\nFinal Y Coordinate: %f\n",
		oldXCoord, oldYCoord);
}

//Returns True if Rover is Stuck.
bool checkStuck (float oldXCoord, float oldYCoord) {

	float errorMargin = 2.0;  //Distance rover can travel and still be stuck
	bool isStuck = false;     //Set to True if Rover is Stuck

	//Compute distance formula from current and previous coordinates
	if (sqrt (pow (getXCoord (oldXCoord) - oldXCoord, 2) +
		  pow (getYCoord (oldYCoord) - oldYCoord, 2)) < errorMargin)  {

		isStuck = true;
	}
	printf ("Rover is Stuck: %d\n", isStuck);
	return isStuck;
}

/************************************************************************
GPS Functions
************************************************************************/

float getXCoord (float oldXCoord) {
	//Either returns the same value as oldXCoord, or
	//has a 1 in 5 chance of returning a different number.
	int chance;

	srand(time (NULL));
	chance = rand() % 5;

	if (chance == 0) {
		return oldXCoord + 10;
	}
	return oldXCoord;       
}

float getYCoord (float oldYCoord) {
	//Either returns the same value as oldYCoord, or
	//has a 1 in 5 chance of returning a different number.
	int chance;

	srand(time (NULL));
	chance = rand() % 5;

	if (chance == 0) {
		return oldYCoord + 10;
	}
	return oldYCoord;       
}

/***********************************************************************
Motor Functions
***********************************************************************/

void roverRotate (float degree) {
	printf ("Rotating %f degrees...\n", degree);
}

void roverForward () {
	printf ("Moving Forward...\n");
}

void roverBackward () {
	printf ("Moving Backward...\n");
}

void roverStop () {
	printf ("Stopped.\n");
}
