#include "main.h"

Finish::Finish () {
	fieldOfView = 90.0;   //View angle of camera for course correction
	waitTime = 2.0;       //Time to wait between course corrections
}

void Finish::touchPole () {

	bool foundPole = false;     //Set to true once pole is found
	bool poleInView = true;     //Set to false once pole is out of view
	int sector = 0;             //Sector of image pole is located
	MotorFuncs myMotor;

	printf ("Testing Find and Touch Finish Pole Module:\n");
	printf ("View Angle: %f\nWait Time: %f\n", fieldOfView, waitTime);
	
	//Rotate and take picture until finding pole
	while (! foundPole) {
		if (! findPole ()) {
			printf ("Did not find pole.\n");
			myMotor.roverRotate (10.);
		}
		else {
			printf ("Did find pole.\n");
			foundPole = true;
		}
	}

	//Head towards the pole until hitting it.
	while (poleInView) {
		myMotor.roverForward ();
		sleep (waitTime);
		myMotor.roverStop ();
		
		sector = findPole ();
		if (sector) {
			//Rotate rover by proportion of view angle of camera
			myMotor.roverRotate ((fieldOfView / 5.0) * (sector - 3));
		}
		else {
			printf ("Pole no longer in view.\n");
			poleInView = false;
		}
	}
	//Continue forward since pole is close enough to not be seen by camera
	myMotor.roverForward ();
	printf ("Hit Pole\n");
}

int Finish::findPole () {
	/*
	  This function will utilize the camera to find the pole.
	  If the pole is in the image, the function returns the
	  sector of the image it's in (1-5), else returns 0

	  Right now, this functionality is simulated.
	*/
	srand(time (NULL));
	return rand() % 6;
}

