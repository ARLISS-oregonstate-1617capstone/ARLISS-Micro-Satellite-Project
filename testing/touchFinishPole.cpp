#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void touchPole ();
int  findPole ();

//Motor Functions
void roverRotate (float);
void roverForward ();
void roverBackward ();
void roverStop ();

int main () {

	touchPole ();
	
	return 0;
}

void touchPole () {

	bool foundPole = false;     //Set to true once pole is found
	bool poleInView = true;     //Set to false once pole is out of view
	float fieldOfView = 90.0;   //View angle of camera for course correction
	int sector = 0;             //Sector of image pole is located
	float waitTime = 2.0;       //Time to wait between course corrections

	printf ("Testing Find and Touch Finish Pole Module:\n");
	printf ("View Angle: %f\nWait Time: %f\n", fieldOfView, waitTime);
	
	//Rotate and take picture until finding pole
	while (! foundPole) {
		if (! findPole ()) {
			printf ("Did not find pole.\n");
			roverRotate (10);
		}
		else {
			printf ("Did find pole.\n");
			foundPole = true;
		}
	}

	//Head towards the pole until hitting it.
	while (poleInView) {
		roverForward ();
		sleep (waitTime);
		roverStop ();
		
		sector = findPole ();
		if (sector) {
			//Rotate rover by proportion of view angle of camera
			roverRotate ((fieldOfView / 5.0) * (sector - 3));
		}
		else {
			printf ("Pole no longer in view.\n");
			poleInView = false;
		}
	}
	//Continue forward since pole is close enough to not be seen by camera
	roverForward ();
	printf ("Hit Pole\n");
}

int findPole () {
	/*
	  This function will utilize the camera to find the pole.
	  If the pole is in the image, the function returns the
	  sector of the image it's in (1-5), else returns 0

	  Right now, this functionality is simulated.
	*/
	srand(time (NULL));
	return rand() % 6;
}

/***********************************************************************
Motor Functions
***********************************************************************/

void roverRotate (float degree) {
	printf ("Rotating %f degrees...\n", degree);
	//Sleeping simulates time taken to rotate
	sleep(2);
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
