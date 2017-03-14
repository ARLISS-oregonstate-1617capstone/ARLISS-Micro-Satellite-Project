#include "main.h"

Parachute::Parachute () {

	curAlt = 2000.0;    //Current Altitude
	minAlt = 500.0;     //Minimum Altitude for Deployment
	finAlt = 0;         //Final Altitude After Deployment
	waitTime = 5.0;     //Number of Seconds to Wait Between Checks
}

void Parachute::deployParachute () {

	GPSFuncs myGPS;
	bool deploy = false;      //Set to True When Depoying

	printf ("Testing Parachute Deployment Module:\n");
	printf ("Deployment Altitude: %f\nWait Time: %f\n",
		minAlt, waitTime);
	
	while (!deploy) {
		curAlt = myGPS.getAltitude (curAlt);
		
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

	finAlt = myGPS.getAltitude (curAlt);
	printf ("Final Altitude: %f\n", finAlt);
}
