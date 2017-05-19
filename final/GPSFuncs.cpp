#include "main.h"

/***************************************************************************
GPS Functions
***************************************************************************/

GPSFuncs::GPSFuncs () {

	if (DEBUG) {
		isStuck = false;
		oldXCoord = 40.753820;    //Latitude in degrees
		oldYCoord = -119.223000;  //Longitude in degrees
		oldZCoord = 1000.;         //Altitude in feet

		srand(time (NULL));
	}
}

double GPSFuncs::getAltitude () {

	if (DEBUG) {
		//This is a testing function. The real function will
		//get data from the GPS unit.
		
		oldZCoord -= 325.7;
		return oldZCoord;
	}
	else {
		while (!gpsReady ());
		struct gps_data data = getGPS ();
		return data.altitude;
	}
}

double GPSFuncs::getXCoord () {

	int degree;
	float minutes;
	float decimalDegree;
	float finalDegree;

	if (DEBUG) {
		//Either returns the same value as oldXCoord, or
		//has a 1 in 5 chance of returning a different number.
		int chance;
		
		chance = rand() % 5;
		
		if (chance == 0) {
			//Each degree is 69 miles, or 364320 feet
			oldXCoord += 0.00005;   //Very small number, about 20 feet
		}
		return oldXCoord;
	}
	else {
		while (!gpsReady ());
		struct gps_data data = getGPS ();

		degree = (int) data.latitude / 100;
		minutes = data.latitude - (degree * 100);
		decimalDegree = minutes / 60.;
		finalDegree = degree + decimalDegree;
			
		return finalDegree;
	}
}

double GPSFuncs::getYCoord () {

	int degree;
	float minutes;
	float decimalDegree;
	float finalDegree;

	if (DEBUG) {
		//Either returns the same value as oldYCoord, or
		//has a 1 in 5 chance of returning a different number.
		int chance;

		chance = rand() % 5;
		
		if (chance == 0) {
			//Each degree is 69 miles, or 364320 feet
			oldYCoord += 0.00005;   //Very small number, about 20 feet
		}
		return oldYCoord;
	}
	else {
		while (!gpsReady ());
		struct gps_data data = getGPS ();

		degree = (int) data.longitude / 100;
		minutes = data.longitude - (degree * 100);
		decimalDegree = minutes / 60.;
		finalDegree = degree + decimalDegree;
		
		return finalDegree;
	}
}
