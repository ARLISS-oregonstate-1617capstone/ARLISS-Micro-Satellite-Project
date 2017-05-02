//Alpha version of obstacle avoidance system for OSU ARLISS Project

#include <string>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
const int Width = 30;
const int Height = 30;


/*
# The Analyze function is the heart of the obstacle avoidance module. this function takes in our image array, and then checks which
# of the three columns (left, center, or right) has the fewest edges and then decides which direction to go based off that data.
#
#
*/
void Analyze(int(Array)[][Height], int rows, int cols) {

	//prints the array
	for (int x = 0; x < rows; x++) {
		std::cout << std::endl;
		for (int y = 0; y < cols; y++) {

			std::cout << Array[x][y] << " ";
		}
	}
	int suml = 0, sumc = 0, sumr = 0;
	//sum left column 
	for (int x = 0; x < 10; x++){
		for (int y = 0; y < rows; y++) {
			suml += Array[y][x];
		}
	}

	std::cout << std::endl << "sum of left section:" << suml << std::endl;

	//sum center column 
	for (int x = 10; x < 20; x++) {
		for (int y = 0; y < rows; y++) {
			sumc += Array[y][x];
		}
	}

	std::cout << std::endl << "sum of center section:" << sumc << std::endl;

	//sum right column 
	for (int x = 20; x < 30; x++) {
		for (int y = 0; y < rows; y++) {
			sumr += Array[y][x];
		}
	}

	std::cout << std::endl << "sum of right section:" << sumr << std::endl;

	//compare results, choose direction

	if (sumc > (suml + 3) && suml <= sumr) {
		std::cout << "Turn left." << std::endl;
	}
	else if (sumc > (sumr + 3) && sumr < suml) {
		std::cout << "Turn right." << std::endl;
	}
	else
		std::cout << "Continue forward." << std::endl;

	return;
}

void main() {

	//open file
	
	std::ifstream infile;
	srand(time(NULL));

/* file I/O that went unused
	infile.open("test.txt");
	if (infile.is_open()) {
		std::cout << "file opened. \n";
			for (unsigned i = 0; i < Width; i++)
				for (unsigned j = 0; j < Height; j++)
					//read in from file, delimited by , and /n to [i][j]
					int k; // holder so it will compile
		infile.close();
	}
	else {
		std::cout << "file wasn't opened.\n";
	}
*/
	//initialize the array with random 0s and 1s, but 0s favored by 85%
	int Image_Array[Width][Height];

	for (int x = 0; x < Width; x++)

		for (int y = 0; y < Height; y++) {
			float f = ((float)rand() / (RAND_MAX));
			int j;
			if (f > .85) {
				j = 1;
			}
			else
				j = 0;
			Image_Array[x][y] = j;
		}

	Analyze(Image_Array, Width, Height);


	std::cin.get();
	return;
}
