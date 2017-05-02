#include "main.h"

LandOnSide::LandOnSide (GPSFuncs* g, MotorFuncs* m ServoFunc* s) {

	waitTime = 4.0;      //Number of Seconds to Wait Between Checks
	//0.00004 degrees is about 15 feet
	errorMargin = 0.00001;   //Distance rover can travel and still be stuck

	myGPS = g;
	myMotors = m;
	myServo = s;
}

void LandOnSide::getUp () {

	float oldXCoord = 0.;   
	float oldYCoord = 0.;   
	bool isSideway = true;       
	
	oldXCoord = myGPS->getXCoord ();
	oldYCoord = myGPS->getYCoord ();
	
	printf ("Testing Get rover stand-up from Landed sideways:\n");
	printf ("long: %f\n lat: %f\nWait Time: %f\n", oldXCoord, oldYCoord, waitTime);
	
	while (isSideway) {
		oldXCoord = myGPS.getXCoord (oldXCoord);
		oldYCoord = myGPS.getYCoord (oldYCoord);
		
		myMotors->roverForward ();
		sleep (waitTime);
		myMotors->roverStop ();

		if (!checkOnSide (oldXCoord, oldYCoord)) {
			isSideway = false;
		}
		else {
		myServo->servoRotate(360); //servo rotates right 360 degrees
		sleep (waitTime);
		}
	}

	printf ("Successfully straight up\n");
}


bool LandOnSide::checkOnSide (float oldXCoord, float oldYCoord) {
	
	bool isSideway = false;     
	
	double dist = sqrt (pow (myGPS->getXCoord () - oldXCoord, 2) + pow (myGPS->getYCoord () - oldYCoord, 2));
	if (dist < errorMargin) {

		isSideway = true;
	}
	printf ("Rover is on its side: %d\n", isSideway);
	return isSideway;
}


