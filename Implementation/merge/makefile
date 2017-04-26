prog: main.o MotorFuncs.o GPSFuncs.o Parachute.o Navigation.o Obstacle.o Unstuck.o Finish.o deviceControl.o
	g++ -g main.o MotorFuncs.o GPSFuncs.o Parachute.o Navigation.o Obstacle.o Unstuck.o Finish.o deviceControl.o -lwiringPi -lpthread -lnmea -lopencv_core -lopencv_highgui -lopencv_imgproc -o prog

main.o: main.h main.cpp
	g++ -Wall -g -c main.cpp

MotorFuncs.o: main.h MotorFuncs.cpp
	g++ -Wall -g -c MotorFuncs.cpp

GPSFuncs.o: main.h GPSFuncs.cpp
	g++ -Wall -g -c GPSFuncs.cpp

Parachute.o: main.h Parachute.cpp
	g++ -Wall -g -c Parachute.cpp

Navigation.o: main.h Navigation.cpp
	g++ -Wall -g -c Navigation.cpp

Obstacle.o: main.h Obstacle.cpp
	g++ -Wall -g -c Obstacle.cpp

Unstuck.o: main.h Unstuck.cpp
	g++ -Wall -g -c Unstuck.cpp

Finish.o: main.h Finish.cpp
	g++ -Wall -g -c Finish.cpp

deviceControl.o: deviceControl.h deviceControl.c
	gcc -Wall -g -c deviceControl.c

clean:
	rm *.o prog
