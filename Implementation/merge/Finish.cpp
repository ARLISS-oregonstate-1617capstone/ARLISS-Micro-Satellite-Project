#include "main.h"

Finish::Finish (MotorFuncs* m) {
	fieldOfView = 90.0;   //View angle of camera for course correction
	waitTime = 2.0;       //Time to wait between course corrections
	srand(time (NULL));   //Seed random number generator for testing

	myMotors = m;
}

void Finish::touchPole () {

	bool foundPole = false;     //Set to true once pole is found
	bool poleInView = true;     //Set to false once pole is out of view
	int sector = 0;             //Sector of image pole is located

	printf ("Testing Find and Touch Finish Pole Module:\n");
	printf ("View Angle: %f\nWait Time: %f\n", fieldOfView, waitTime);
	
	//Rotate and take picture until finding pole
	while (! foundPole) {
		if (! findPole ()) {
			printf ("Did not find pole.\n");
			myMotors->roverRotate (10.);
		}
		else {
			printf ("Did find pole.\n");
			foundPole = true;
		}
	}

	//Head towards the pole until hitting it.
	while (poleInView) {
		myMotors->roverForward ();
		sleep (waitTime);
		myMotors->roverStop ();
		
		sector = findPole ();
		if (sector) {
			//Rotate rover by proportion of view angle of camera
			myMotors->roverRotate ((fieldOfView / 5.0) * (sector - 3));
		}
		else {
			printf ("Pole no longer in view.\n");
			poleInView = false;
		}
	}
	//Continue forward since pole is close enough to not be seen by camera
	myMotors->roverForward ();
	printf ("Hit Pole\n");
}

int Finish::findPole () {
	/*
	  This function will utilize the camera to find the pole.
	  If the pole is in the image, the function returns the
	  sector of the image it's in (1-5), else returns 0

	  Right now, this functionality is simulated.
	*/
	return rand() % 3;
}

