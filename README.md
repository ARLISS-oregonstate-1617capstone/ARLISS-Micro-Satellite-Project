# ARLISS Micro Satellite Project

ARLISS (A Rocket Launch for International Student Satellites) is an international competition between students to build, launch, and recover prototype satellites. This is the Oregon State University Computer Science team's repository.

# Description

Our software is responsible for deploying a parachute when the satellite is disconnected from the rocket and autonomously navigating to specific GPS coordinates, avoiding obstacles along the way. 

# Prerequisites

For testing Version:

    OpenCV V 2.4.9
    
    Linux Machine

Additionally, to run on actual hardware:

    Raspberry Pi Zero
    
    wiringPi (PIN based GPIO access library for the raspberry pi)

The satellite uses a raspberry pi zero connected a custom PCB board to operate various sensors and motors. To test the code on any linux machine, set the DEBUG variable in final/main.h to 1. If DEBUG is set to 0, the program will attempt to communicate with motors which most likely don't exist or aren't configured correctly on any hardware other than the custom hardware designed for the satellite.

# Installing

To compile, simply run the makefile located in the final directory. To run the test version on any machine type make test with the DEBUG variable set to 1 in main.h. To run on the actual satellite hardware type make final with the DEBUG variable set to 0 (by default set to test version with DEBUG = 1). 
