CC = g++
CFLAGS = -Wall -g -c
LIBS = `pkg-config opencv --cflags --libs`
DEPS = main.h
SRC = main.cpp MotorFuncs.cpp GPSFuncs.cpp Parachute.cpp Navigation.cpp Obstacle.cpp Unstuck.cpp Finish.cpp
OBJ = $(SRC:.cpp=.o)

.cpp.o: $(DEPS)
	$(CC) $(CFLAGS) $<

test: $(OBJ)
	$(CC) -g $(OBJ) $(LIBS) -o test

final: $(OBJ) deviceControl.o
	$(CC) -g $(OBJ) deviceControl.o -lwiringPi -lpthread -lnmea $(LIBS) -o final

deviceControl.o: deviceControl.h deviceControl.c
	gcc $(CFLAGS) deviceControl.c

clean:
	rm -f *.o final test
