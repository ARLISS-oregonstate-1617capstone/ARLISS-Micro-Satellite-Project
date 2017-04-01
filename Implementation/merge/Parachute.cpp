#include "main.h"

Parachute::Parachute (GPSFuncs* g, MotorFuncs* m) {

	minAlt = 500.0;     //Minimum Altitude for Deployment
	waitTime = 5.0;     //Number of Seconds to Wait Between Checks

	myGPS = g;
	myMotors = m;
}

void Parachute::deployParachute () {

	bool deploy = false;      //Set to True When Depoying
	float curAlt = 0.;        //Current Altitude
	float finAlt = 0.;        //Final Altitude After Deployment
	
	printf ("Testing Parachute Deployment Module:\n");
	printf ("Deployment Altitude: %f\nWait Time: %f\n",
		minAlt, waitTime);
	
	while (!deploy) {
		curAlt = myGPS->getAltitude ();
		
		printf ("Altitude: %f\n", curAlt);
		if (curAlt > minAlt)
			sleep (waitTime);
		else {
			printf("Below Minimum Altitude\n");
			
			sleep (waitTime);
			if (curAlt < minAlt)
				deploy = true;
		}
	}
	printf ("Deploying Parachute...\n");
	myMotors->deployParachute ();
	
	finAlt = myGPS->getAltitude ();
	printf ("Final Altitude: %f\n", finAlt);
}
