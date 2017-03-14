#include <string>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <iomanip>

class MotorFuncs;
class GPSFuncs;
class Parachute;
class Navigation;
class Obstacle;
class Unstuck;
class Finish;
class Program;

// Class to hold all Motor functions
class MotorFuncs {
 public:
	void roverRotate (float);
	void roverForward ();
	void roverBackward ();
	void roverStop ();
};

// Class to hold all GPS functions
class GPSFuncs {
 public:
	float getAltitude (float);
	float getXCoord (float);
	float getYCoord (float);
};

// Class for parachute deployment
class Parachute {
 public:
	Parachute ();
	void deployParachute ();
 private:
	float curAlt;
	float minAlt;
	float finAlt;
	float waitTime;
};

// Class for navigation to finish coordinates
class Navigation {
 public:
	void startNavigation ();
 private:
	double degreetoRadian (double);
	double radiantoDegree (double);
	double calcDist (double, double, double, double);
	double calcBearing (double, double, double, double);
	void navigation (double, double, double, double);
};

// Class to avoid obstacles
class Obstacle {
 public:
	void checkObstacle ();
 private:
	static const int Width = 30;
	static const int Height = 30;
	void Analyze (int(Array)[][Height], int, int);
};

// Class to get rover unstuck from obstacle 
class Unstuck {
 public:
	Unstuck ();
	void getUnstuck ();
 private:
	bool checkStuck (float, float, GPSFuncs);
	float waitTime;    //Number of Seconds to Wait Between Checks
	float errorMargin; //Distance rover can travel and still be stuck
};

// Class to touch the finish pole
class Finish {
 public:
	Finish ();
	void touchPole ();
 private:
	int findPole ();
	float fieldOfView;
	float waitTime;
};

// Class to run program
class Program {
 public:
	void start (); //Starts program
};

