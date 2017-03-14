#include "main.h"

void Program::start () {

	Parachute ParachuteModule;
	Navigation NavigationModule;
	Obstacle ObstacleAvoidance;
	Unstuck GetUnstuckModule;
	Finish FindFinishModule;

	//Deploy Parachute
	printf("\n\n------Parachute------\n\n");
	ParachuteModule.deployParachute ();

	//Navigate to final Coordinates
	printf("\n\n------Navigation------\n\n");
	NavigationModule.startNavigation ();

	//Check for obstacles in path
	printf("\n\n------Obstacle------\n\n");
	ObstacleAvoidance.checkObstacle ();
	
	//Get Unsuck from Obstacle
	printf("\n\n------Unstuck------\n\n");
	GetUnstuckModule.getUnstuck ();

	//Touch the finish pole
	printf("\n\n------Finish------\n\n");
	FindFinishModule.touchPole ();

	printf("\n\n------Complete------\n\n");
}
