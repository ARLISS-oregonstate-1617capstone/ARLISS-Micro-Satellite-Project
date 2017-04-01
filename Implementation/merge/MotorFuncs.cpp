/***********************************************************************
Motor Functions
***********************************************************************/

#include "main.h"

void MotorFuncs::roverRotate (float degree) {
	printf ("Rotating %f degrees...\n", degree);
}

void MotorFuncs::roverForward () {
	printf ("Moving Forward...\n");
}

void MotorFuncs::roverBackward () {
	printf ("Moving Backward...\n");
}

void MotorFuncs::roverStop () {
	printf ("Stopped.\n");
}

void MotorFuncs::deployParachute () {
	printf ("Deploying parachute...\n");
}
