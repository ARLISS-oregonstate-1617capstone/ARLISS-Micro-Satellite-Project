# motorControl
Functions for use:

## void moveForward(int speed)
Moves the CanSat forwards at speed "speed". This int should be from 0-10.

## void moveBackward(int speed)
Moves the CanSat backwards at speed "speed". This int should be from 0-10.

## void halt()
Stops the CanSat.

## void turnRightHard(int angle)
Turns the CanSat to the right hard, as in the right motor moves in reverse 
while the left moves forward. If the previous action was halt, then it does 
this at speed 5, otherwise it does it at the previous speed.

## void turnRightSoft(int angle)
Turns the CanSat to the right softly, as in the right motor slows to half 
the current speed. If the previous action was halt, then it does this at speed
5.

## void turnLeftHard(int angle)
Turns the CanSat to the left hard, as in the left motor moves in reverse 
while the right moves forward. If the previous action was halt, then it does 
this at speed 5, otherwise it does it at the previous speed.

## void turnLeftSoft(int angle)
Turns the CanSat to the left softly, as in the left motor slows to half 
the current speed. If the previous action was halt, then it does this at speed
5.

## int motorReady()
Returns a one when the thread is ready to accept commands, and a 0 when it is
not.

## int currentAction()
Returns the current action:
	1 - Forward
	2 - Backward
	3 - Halt
	4 - Turning Right
	5 - Turning Left

## int currentSpeed()
Returns the current speed.
