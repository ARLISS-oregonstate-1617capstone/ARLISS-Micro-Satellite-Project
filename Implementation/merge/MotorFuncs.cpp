/***********************************************************************
Motor Functions
***********************************************************************/

#include "main.h"

void MotorFuncs::roverRotate (double degree) {
	printf ("Rotating %f degrees...\n", degree);

	if (!DEBUG) {
		if (degree < 0) {
			while (!motorReady ()) sleep (1);
			turnLeftBlocking (abs((int) degree));
		}
		else {
			while (!motorReady ()) sleep (1);
			turnRightBlocking ((int) degree);
		}
	}
}

void MotorFuncs::roverForward () {
	printf ("Moving Forward...\n");

	if (!DEBUG) {
		while (!motorReady ()) sleep (1);
		moveForward ();
	}
}

void MotorFuncs::roverBackward () {
	printf ("Moving Backward...\n");

	if (!DEBUG) {
		while (!motorReady ()) sleep (1);
		moveBackward ();
	}
}

void MotorFuncs::roverStop () {
	printf ("Stopped.\n");

	if (!DEBUG) {
		while (!motorReady ()) sleep (1);
		halt ();
	}
}

void MotorFuncs::deployParachute () {
	printf ("Deploying parachute...\n");
}
