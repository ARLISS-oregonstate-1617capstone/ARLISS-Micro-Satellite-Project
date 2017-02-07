#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void deployParachute ();

//GPS Function
float getAltitude (float);

int main () {

	deployParachute ();
	return 0;
}

void deployParachute () {

	float curAlt = 2000.0;    //Current Altitude
	float minAlt = 500.0;     //Minimum Altitude for Deployment
	float finAlt = 0;         //Final Altitude After Deployment
	float waitTime = 5.0;     //Number of Seconds to Wait Between Checks
	bool deploy = false;      //Set to True When Depoying

	printf ("Testing Parachute Deployment Module:\n");
	printf ("Deployment Altitude: %f\nWait Time: %f\n",
		minAlt, waitTime);
	
	while (!deploy) {
		curAlt = getAltitude (curAlt);
		
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

	finAlt = getAltitude (curAlt);
	printf ("Final Altitude: %f\n", finAlt);
}

/***************************************************************************
GPS Function
***************************************************************************/

float getAltitude (float curAlt) {
	//This is a testing function. The real function will
	//get data from the GPS unit.

	return curAlt - 325.7;
}
