/***********************************************************************
Servo Functions 

We haven't yet had any servo function implemented by the ECE team, so here use motor function as dummy
***********************************************************************/

#include "main.h"

void ServoFuncs::servoRotate (double degree) {
	printf ("Servo rotates %f degrees...\n", degree);

	if (!DEBUG) {
		if (degree < 0) {
			while (!servoReady ()) sleep (1);
			turnLeftBlocking (abs((int) degree));
		}
		else {
			while (!servoReady ()) sleep (1);
			turnRightBlocking ((int) degree);
		}
	}
}


void ServoFuncs::servoMoveUp () {
	printf ("Servo moves up...\n");

	if (!DEBUG) {
		while (!servoReady ()) sleep (1);
		servoUp ();
	}
}

void ServoFuncs::servoMoveDown () {
	printf ("Servo moves down...\n");

	if (!DEBUG) {
		while (!servoReady ()) sleep (1);
		servoDown ();
	}
}