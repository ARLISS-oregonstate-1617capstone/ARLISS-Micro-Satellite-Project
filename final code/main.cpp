#include "main.h"

int main () {

	GPSFuncs myGPS;
	MotorFuncs myMotors;
	//ServoFuncs myServos;
	
	Parachute ParachuteModule (&myGPS, &myMotors);
	Navigation NavigationModule (&myGPS, &myMotors);
	Obstacle ObstacleAvoidance (&myMotors);
	Unstuck GetUnstuckModule (&myGPS, &myMotors);
	//LandOnSide GetRoverUpModule (&myGPS, &myMotors, &myServos);
	Finish FindFinishModule (&myMotors);

	//Initialize GPS, Accelerometer, and Motors
	//(Required for GPSFuncs and MotorFuncs Classes)
	if (!DEBUG) {
		deviceInit ();
	}
	  
	//Deploy Parachute
	printf("\n\n------Parachute------\n\n");
	ParachuteModule.deployParachute ();

	//Navigate to final Coordinates
	printf("\n\n------Navigation------\n\n");
	NavigationModule.startNavigation ();

	//Check for obstacles in path
	printf("\n\n------Obstacle------\n\n");
	ObstacleAvoidance.checkObstacle ();
	
	//Get Unstuck from Obstacle
	printf("\n\n------Unstuck------\n\n");
	GetUnstuckModule.getUnstuck ();
	
	/*
	//Get Up from Sideways
	printf("\n\n------GetRoverUp------\n\n");
	GetRoverUpModule.getUp ();
	*/

	//Touch the finish pole
	printf("\n\n------Finish------\n\n");
	FindFinishModule.touchPole ();

	printf("\n\n------Complete------\n\n");

	return 0;
}
