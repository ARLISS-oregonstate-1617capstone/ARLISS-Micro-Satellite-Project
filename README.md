# ARLISS Micro Satellite Project

ARLISS (A Rocket Launch for International Student Satellites) is an international competition between students to build, launch, and recover prototype satellites. This is the Oregon State University Computer Science team's repository.

# Description

Our software is responsible for deploying a parachute when the satellite is disconnected from the rocket and autonomously navigating to specific GPS coordinates, avoiding obstacles along the way. 

# Prerequisites

OpenCV V 2.4.9

Linux Machine

The satellite uses a raspberry pi zero connected a custom PCB board to operate various sensors and motors. To test the code on any linux machine, set the DEBUG variable in main.h to 1. If DEBUG is set to 0, the program will attempt to communicate with motors which most likely don't exist or aren't configured correctly on any hardware other than the custom hardware designed for the satellite.

# Installing

To compile, simply run the makefile located in Implementation/merge. To start, run the prog executable created from the makefile.
