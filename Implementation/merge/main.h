#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class MotorFuncs;
class GPSFuncs;
class Parachute;
class Navigation;
class Obstacle;
class Unstuck;
class Finish;

// Class to hold all Motor functions
class MotorFuncs {
 public:
	void roverRotate (double);
	void roverForward ();
	void roverBackward ();
	void roverStop ();
	void deployParachute ();
};

// Class to hold all GPS functions
class GPSFuncs {
 public:
	GPSFuncs ();
	double getAltitude ();
	double getXCoord ();
	double getYCoord ();
 private:
	bool isStuck;
	double oldXCoord;
	double oldYCoord;
	double oldZCoord;
};

// Class for parachute deployment
class Parachute {
 public:
	Parachute (GPSFuncs*, MotorFuncs*);
	void deployParachute ();
 private:
	double minAlt;
	double waitTime;
	
	GPSFuncs* myGPS;
	MotorFuncs* myMotors;
};

// Class for navigation to finish coordinates
class Navigation {
 public:
	Navigation (GPSFuncs*, MotorFuncs*);
	void startNavigation ();
 private:
	double degreetoRadian (double);
	double radiantoDegree (double);
	double calcDist (double, double);
	double calcBearing (double, double);
	void navigation (double, double);

	double destLat;     //Latitude of Finish
	double destLong;    //Longitude of Finish
	
	GPSFuncs* myGPS;
	MotorFuncs* myMotors;
};

// Class to avoid obstacles
class Obstacle {
 public:
	Obstacle (MotorFuncs*);
	void checkObstacle ();
 private:
	static const int Width = 1920;
	static const int Height = 1080;
	int threshval;
	void Analyze (int(Array)[][Height], int, int);
	void createTrackbars();
	void createTrackbars2();

	MotorFuncs* myMotors;
};

// Class to get rover unstuck from obstacle 
class Unstuck {
 public:
	Unstuck (GPSFuncs*, MotorFuncs*);
	void getUnstuck ();
 private:
	bool checkStuck (double, double);
	double waitTime;    //Number of Seconds to Wait Between Checks
	double errorMargin; //Distance rover can travel and still be stuck

	GPSFuncs* myGPS;
	MotorFuncs* myMotors;
};

// Class to touch the finish pole
class Finish {
 public:
	Finish (MotorFuncs*);
	void touchPole ();
 private:
	int findPole ();
	double fieldOfView;
	double waitTime;

	MotorFuncs* myMotors;
};

