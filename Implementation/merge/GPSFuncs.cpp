#include "main.h"

/***************************************************************************
GPS Functions
***************************************************************************/

float GPSFuncs::getAltitude (float curAlt) {
	//This is a testing function. The real function will
	//get data from the GPS unit.

	return curAlt - 325.7;
}

float GPSFuncs::getXCoord (float oldXCoord) {
	//Either returns the same value as oldXCoord, or
	//has a 1 in 5 chance of returning a different number.
	int chance;

	srand(time (NULL));
	chance = rand() % 5;

	if (chance == 0) {
		return oldXCoord + 10;
	}
	return oldXCoord;       
}

float GPSFuncs::getYCoord (float oldYCoord) {
	//Either returns the same value as oldYCoord, or
	//has a 1 in 5 chance of returning a different number.
	int chance;

	srand(time (NULL));
	chance = rand() % 5;

	if (chance == 0) {
		return oldYCoord + 10;
	}
	return oldYCoord;       
}
