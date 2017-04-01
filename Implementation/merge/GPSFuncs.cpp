#include "main.h"

/***************************************************************************
GPS Functions
***************************************************************************/

GPSFuncs::GPSFuncs () {

	isStuck = false;
	oldXCoord = 100.;
	oldYCoord = 200.;
	oldZCoord = 1000.;

	srand(time (NULL));
}

float GPSFuncs::getAltitude () {
	//This is a testing function. The real function will
	//get data from the GPS unit.

	oldZCoord -= 325.7;
	return oldZCoord;
}

float GPSFuncs::getXCoord () {
	//Either returns the same value as oldXCoord, or
	//has a 1 in 5 chance of returning a different number.
	int chance;

	chance = rand() % 5;

	if (chance == 0) {
		oldXCoord += 10;
	}
	return oldXCoord;       
}

float GPSFuncs::getYCoord () {
	//Either returns the same value as oldYCoord, or
	//has a 1 in 5 chance of returning a different number.
	int chance;

	chance = rand() % 5;

	if (chance == 0) {
		oldYCoord += 10;
	}
	return oldYCoord;       
}
