#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef A_H
#define A_H

struct gps_data {
	float latitude;
	float longitude;
	float altitude;
	char* lat_heading;
	char* long_heading;
	int   status;
	int   time;
};

#endif

#ifndef B_H
#define B_H

struct accel_data {
	float x;
	float y;
	float z;
};

#endif

extern int curSpeed;
extern int curAction;
extern int action;
extern int threadReady;
extern int angleSpeed_i;

void moveForward();			
void moveForwardBlocking();	
void moveBackward();
void moveBackwardBlocking();
void halt();
void haltBlocking();
void turnRight(int angle);
void turnRightBlocking(int angle);
void turnLeft(int angle);
void turnLeftBlocking(int angle);
int  motorReady();
int  motorAction();
struct accel_data getAccel();
struct gps_data getGPS();
int gpsReady ();	
void deviceInit();

#ifdef __cplusplus
}
#endif
