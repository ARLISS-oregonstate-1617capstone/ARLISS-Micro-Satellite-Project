#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <pthread.h>
#include <time.h>
#include "deviceControl.h"

int curAction     = 0;	// Indicates current action
int action        = 0;	// Communication to thread
int threadReady   = 0;	// Communication indicating thread is busy
int duration  	  = 0;	// Communication to thread
int gps_ready     = 0;	// One if the gps has new data

struct gps_data gps_global;
struct accel_data accel_global;

#define rightMotorForward   24 // First right motor control pin       WHITE
#define rightMotorReverse   25 // Second right motor control pin      BLACK
#define leftMotorForward    18 // First motor control pin             PURPLE
#define leftMotorReverse    23 // Second left motor control pin	 	  BLUE

#define high_af  1  // Unsure if active high or low so easily changed here
#define low_af   0  // Likewise

/*******************************************************************************
/ void moveForward
/ This functios takes in a speed, and then translates it into forward motion
/ On the CanSat. The integer speed will be from 1-10. This func is non-blocking
*******************************************************************************/
void moveForward(){
	action = 1;				// Alert thread to move forward.
	threadReady = 0;		// Make sure no other functions are called.
	return;
}//moveFoward

/*******************************************************************************
/ void moveForwardBlocking
/ This functios takes in a speed, and then translates it into forward motion
/ On the CanSat. The integer speed will be from 1-10. This func is blocking
*******************************************************************************/
void moveForwardBlocking() {
	digitalWrite(rightMotorReverse, low_af);
	digitalWrite(rightMotorForward, high_af); // Make direction Right forward
	digitalWrite(leftMotorReverse,  low_af); // Make direction Left forward
	digitalWrite(leftMotorForward,  high_af);
	curAction = 1; 		// We are now moving foward 
}//moveForwardBlocking

/*******************************************************************************
/ void moveBackward
/ This functions takes in a speed, and then translates it into backward motion
/ On the CanSat. The integer speed will be from 1-10.
*******************************************************************************/
void moveBackward(){
	action = 2;				// Alert thread to move backward.
	threadReady = 0;		// Make sure no other functions are called.
	return;
}//moveBackward

/*******************************************************************************
/ void moveBackwardBlocking
/ This functions takes in a speed, and then translates it into backward motion
/ On the CanSat. The integer speed will be from 1-10. This func is blocking
*******************************************************************************/
void moveBackwardBlocking() {
	digitalWrite(rightMotorForward, low_af);	// Write first transistor.
	digitalWrite(rightMotorReverse, high_af);  	// Write seconde transistor.
	digitalWrite(leftMotorForward,  low_af);	// Write first transistor.
	digitalWrite(leftMotorReverse,  high_af);	// Write second transistor.
	curAction = 2;    	// Update current action
}//MoveBackwardBlocking

/*******************************************************************************
/ void halt
/ This functions makes the CanSat stop moving.
*******************************************************************************/
void halt() {
	action = 3;			// Alert thread to stop CanSat
	threadReady = 0;	// Make sure no other functions are called.
	return;
}//halt

/*******************************************************************************
/ void haltBlocking
/ This functions makes the CanSat stop moving. This func is blocking.
*******************************************************************************/
void haltBlocking() {	
	digitalWrite(rightMotorForward, low_af);	// Write first transistor.
	digitalWrite(rightMotorReverse, low_af);  	// Write seconde transistor.
	digitalWrite(leftMotorForward,  low_af);	// Write first transistor.
	digitalWrite(leftMotorReverse,  low_af);	// Write second transistor.
	curAction  = 3;		// Update current action.
}//haltBlocking

/*******************************************************************************
/ void turnRight
/ This functions takes in an angle, and then translates it into a right turn
/ at that angle. The integer angle will be from 0-360. Any angle greater than
/ 45 degrees will require a full stop before turning. The CanSat will then
/ continue doing whatever it was doing before. This func is non-Blocking
*******************************************************************************/
void turnRight(int dur){
	duration = dur;	 		// Give thread the duration to turn.
	action = 4;				// Alert thread to turn.
	threadReady = 0;		// Make sure no other functions are called.
}//turnRight

/*******************************************************************************
/ void turnRightHardBlocking
/ This functions takes in an angle, and then translates it into a right turn
/ at that angle. The integer angle will be from 0-360. Any angle greater than
/ 45 degrees will require a full stop before turning. The CanSat will then
/ continue doing whatever it was doing before. This function is blocking 
*******************************************************************************/
void turnRightBlocking(int dur) {
	
	int prevAction = curAction; // What we were doing before

	curAction = 4;  // Reset our current action
	
	// Begin turn
	digitalWrite(rightMotorReverse, low_af);	// Right motor foward
	digitalWrite(rightMotorForward, high_af);  	// 
	digitalWrite(leftMotorForward,  low_af);	// Left motor reverse
	digitalWrite(leftMotorReverse,  high_af);	// 
	
	delay(dur);

	// Do whatever we were doing.	
	if (prevAction == 1) { // if we were moving forward
		moveForwardBlocking();
	} //if prevAction
	else if (prevAction == 2) {  // If we were backing up 
		moveBackwardBlocking();
	} //else if prevAction
	else if (prevAction == 3) { // We were stopped.
		haltBlocking();   // Now we aren't.
	} //else if prevAction
}//turnRightHardBlocking

/*******************************************************************************
/ void turnLeft
/ This functions takes in an angle, and then translates it into a left turn
/ at that angle. The integer angle will be from 0-180. Any angle greater than
/ 45 degrees will require a full stop before turning.
*******************************************************************************/
void turnLeft(int dur){
	duration = dur;	// Give thread the angle to turn.
	action = 5;				// Alert thread to turn left.
	threadReady = 0;		// Make sure no other functions are called.
	return;
}//turnLeftHard

/*******************************************************************************
/ void turnLeftHardBlocking
/ This functions takes in an angle, and then translates it into a right turn
/ at that angle. The integer angle will be from 0-360. Any angle greater than
/ 45 degrees will require a full stop before turning. The CanSat will then
/ continue doing whatever it was doing before. This function is blocking 
*******************************************************************************/
void turnLeftBlocking(int dur) {
	
	int prevAction = curAction; // What we were doing before

	curAction = 5;  // Reset our current action
	
	// Begin turn
	digitalWrite(leftMotorReverse,  low_af);		// Left motor foward
	digitalWrite(leftMotorForward,  high_af);  	// 
	digitalWrite(rightMotorForward, low_af);	// Right motor reverse
	digitalWrite(rightMotorReverse, high_af);	// 
	
	delay(dur);      // Delay for specified time then do whatever we were doing
		
	// Do whatever we were doing.	
	if (prevAction == 1) { // if we were moving forward
		moveForwardBlocking();
	} //if prevAction
	else if (prevAction == 2) {  // If we were backing up 
		moveBackwardBlocking();
	} //else if prevAction
	else if (prevAction == 3) { // We were stopped.
		haltBlocking();   // Now we aren't.
	} //else if prevAction
}//turnLeftBlocking

/***************************************************************************** 
/ motorReady
/ Returns 0 if the thread is doing an operation, i.e. in the process of 
/ turning. Returns a 1 if the motor is ready to accept commands.
*****************************************************************************/
int motorReady() {
	return threadReady; // threadReady is one when the thread is ready.
}

/*****************************************************************************
/ motorAction
/ Returns the current motor action (1) means moving forward, (2) means moving
/ backward, (3) means halting, (4) means turning right, (5) means turning 
/ left.
*****************************************************************************/
int motorAction() {
	return curAction;
}

/*****************************************************************************
/ motorThread
/ This is the thread that controls the motors. It is started when you call
/ initGPIO.
*****************************************************************************/
PI_THREAD (motorThread) {

	threadReady = 1;	// The thread has started.
	while(1) {					
		if (action == 1) { // Move forward
			moveForwardBlocking(); // Move forward
			delay(500); // .5 second switching time... >:|
			action = 0;				 // Reset the action 
			threadReady = 1;		 // Thread is ready to accept more commands.
		}// Move foward
		else if (action == 2) {	//move backward
			moveBackwardBlocking(); // Move backward 
			delay(500); // .5 second switching time >:|
			action = 0;			// Reset the action
			threadReady = 1;	// The thread is ready to accept more commands.
		}// move backward
		else if (action == 3) { //halt
			haltBlocking(); // Stop fam.
			delay(500);  // .5 second switching time
			action = 0; 		// Reset the action
			threadReady = 1;    // Thread is ready to accept commands.
		}//halt
		else if (action == 4) { //turn right hard
			turnRightBlocking(duration);	// Turn right
			delay(500); // .5 second switching time.
			action = 0;			// Reset the action
			threadReady = 1; 	// Thread is ready to accept commands
		}//turn right
		else if (action == 5) { //turn left
			turnLeftBlocking(duration); 	// Turn left
			delay(500); // .5 second switching time.
			action = 0;
			threadReady = 1;
		}//turn left
	}//while
}//thread


/*****************************************************************************/
/******************************** ACCELEROMETER ******************************/
/*****************************************************************************/


/******************************************************************************
/	xaccel(fd) 
/	This program takes in a token for an I2C device (specifically, the 
/	accelerometer), and returns the acceleration in the x direction in g's.
******************************************************************************/
float xaccel(fd) {
	int lowbyte = wiringPiI2CReadReg8(fd,0x28);		// Read the low byte
	int highbyte = wiringPiI2CReadReg8(fd,0x29);	// Read the high byte
	int16_t value = ((highbyte<<8)|lowbyte);		// Store in 16 bit #

	float val_g = value*12/65536.0;					// Convert to G's
	return val_g;									// Return g's in x dir
}

/******************************************************************************
/	yaccel(fd) 
/	This program takes in a token for an I2C device (specifically, the 
/	accelerometer), and returns the acceleration in the y direction in g's.
******************************************************************************/
float yaccel(fd) {
	int lowbyte = wiringPiI2CReadReg8(fd,0x2A);		// Read the low byte
	int highbyte = wiringPiI2CReadReg8(fd,0x2B);	// Read the high byte
	int16_t value = ((highbyte<<8)|lowbyte);		// store in 16 bit #

	float val_g = value*12/65536.0;					// Convert to g's
	return val_g;									// Return g's in y dir
}

/******************************************************************************
/	zaccel(fd) 
/	This program takes in a token for an I2C device (specifically, the 
/	accelerometer), and returns the acceleration in the z direction in g's.
******************************************************************************/
float zaccel(fd) {
	int lowbyte = wiringPiI2CReadReg8(fd,0x2C);		// Read the low byte
	int highbyte = wiringPiI2CReadReg8(fd,0x2D);	// Read the high byte
	int16_t value = ((highbyte<<8)|lowbyte);		// Store in 16 bit #
	
	float val_gravity = value*12/65536.0;			// Convert to g's
	return val_gravity;								// return G's in z dir
}

/******************************************************************************
/	getAccel()
/	Returns a struct containing the g's in each of the three directions (each
/	can be accessed by accel_data.x, accel_data.y, etc. Each element is a 
/	float
******************************************************************************/
struct accel_data getAccel() {
	return accel_global;			// Global variable updated in accelthread
}

/*****************************************************************************
/	accelThread
/	Continuously updates the global variable storing the accelerometer data
*****************************************************************************/
PI_THREAD(accelThread) {
	int fd = wiringPiI2CSetup(0x19);			// Address of accel is 0x19
	wiringPiI2CWriteReg8(fd, 0x20, 0b10100111);	// 5 Hz, all axes
	while(1) {
		accel_global.x = xaccel(fd);			// Store x in global struct
		accel_global.y = yaccel(fd);			// Store y in global struct
		accel_global.z = zaccel(fd);			// Store z in global struct
		delay(10);								// Wait a hot sec
	}//while
}//thread


/*****************************************************************************/
/************************************ GPS ************************************/
/*****************************************************************************/


/*****************************************************************************
/	gpsReady()
/	Returns a one if the gps has new data to be read.
*****************************************************************************/
int gpsReady() {
	if(gps_ready) {		// If the gps has new data
		gps_ready = 0;	// Reset gps_ready
		return 1;		// Return a one
	}
	else {
		return 0;		// the gps isn't ready, return a 0
	}
}//gpsReady

/*****************************************************************************
/	getGPS()
/	Returns the data struct holding the current GPS location, time, and 
/	altitude.
*****************************************************************************/
struct gps_data getGPS() {
	return gps_global;
}

/*****************************************************************************
/	gpsParcer(char str[200])
/	If there is a signal, then this will parse the data and store it into the
/	global gps data struct, and alerts gps_ready that there is new data
*****************************************************************************/
void gpsParcer(char str[200]) {
	const char s[2] = ",";	// Used for parsing
	char *token;			// Used for parsing
	char *array[11];		// Stores parsed strings
	int i = 0;				// Used for counting

	token = strtok(str,s);	// Parses until next , (stored in s)
	if(strncmp(token, "$GPGGA",6) == 0) { 	// This is how the nmea 0183 parses
		while(token != NULL) {				// Until NULL
			array[i] = token;				// Stores tokens
			i++;							// Increment count
			token = strtok(NULL,s);			// I don't really know?
		}
		gps_global.status = atoi(array[6]); 	// Set's status 
		//printf("%s",token);
		if(strncmp(array[6],"1",1) == 0 | strncmp(array[6],"2",1) == 0) {
			gps_global.latitude = atof(array[2]);	// Store lat
			gps_global.longitude = atof(array[4]);	// Store long
			gps_global.altitude = atof(array[9]);	// Store alt
			gps_global.lat_heading = array[3];		// Store lat heading
			gps_global.long_heading = array[5];		// Store long haeding
			gps_global.time = atoi(array[1]);		// Store time
			gps_ready = 1;					// GPS has new data
		}
	}
}

/*****************************************************************************
/	gpsThread()
/	Reads in data from the GPS using UART
*****************************************************************************/
PI_THREAD(gpsThread) {
	char sentence[200];					// Stores Current data from gps
	int handle = serialOpen("/dev/ttyAMA0",9600);	// Opens connection to gps
	int i = 0;							// Current character being read in
	serialFlush(handle);				// Flush input dta
	while (1) {	
		i = 0;		// Reset count
		while(serialDataAvail(handle)) {		// We have data!
			sentence[i] = serialGetchar(handle);	// Read in a char at a time
			//printf("serial %c\n",sentence[i]);
			i++;								// increment count 	
			delay(1);							// Wait a hot sec
			if(sentence[i-1] == '\n') {			// If we reached the \n
				gpsParcer(sentence);			// Parse sentence
				i++;							// Inc count
				while (i!=0) {					// Clear sentence
					i--;						// Decrement count
					sentence[i] = '\0';			// Set to null
				}
			}
		}
	}
}


void servoUp() {
	system("sudo echo 7=2250us > /dev/servoblaster");
}

void servoDown() {
	system("sudo echo 7=750us > /dev/servoblaster");
}

/****************************************************************************
/ void deviceInit
/ Thus far, this function only calls wiringPiSetupGpio in order to initialize
/ the necessary GPIO logic, and also starts the motor controlling thread. It 
/ also ensures the CanSat is not moving.
*****************************************************************************/
void deviceInit(void) {
	//wiringPiSetup();		// Simplified version
	wiringPiSetupGpio();	// Broadcom versioni
	system("sudo killall servod");	
	// Start threads
	piThreadCreate(motorThread); // Start the motor controlling thread.
	piThreadCreate(accelThread); // Start the accelerometer.
	piThreadCreate(gpsThread);	 // Start the GPS
	
	// Setup GPIO pins
	pinMode(rightMotorReverse, OUTPUT);	// init right motor reverse
	pinMode(rightMotorForward, OUTPUT);	// init right motor forward
	pinMode(leftMotorReverse,  OUTPUT); // init left motor reverse
	pinMode(leftMotorForward,  OUTPUT); // init left motor forward
	
	// Make sure we are stopped
	haltBlocking();
}


