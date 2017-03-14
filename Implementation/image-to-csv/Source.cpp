#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sstream>

//#include "opencv-3.2.0/modules/imgproc/include/opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv-3.2.0/modules/highgui/include/opencv2/highgui/highgui.hpp"
//#include "opencv-3.2.0/modules/core/include/opencv2/core/core.hpp"

using namespace cv;
using namespace std;

const int Width = 800;
const int Height = 600;

int threshval = 150;
void on_trackbar(int, void*);
void createTrackbars();


/*
# The Analyze function is the heart of the obstacle avoidance module. this function takes in our image array, and then checks which
# of the three columns (left, center, or right) has the fewest edges and then decides which direction to go based off that data.
#
#
*/
void Analyze(int(Array)[][Height], int rows, int cols) {

	//prints the array
	for (int x = 0; x < rows; x++) {
		cout << endl;
		for (int y = 0; y < cols; y++) {

			cout << Array[x][y] << " ";
		}
	}
	int suml = 0, sumc = 0, sumr = 0;
	//sum left column 
	for (int x = 0; x < 267; x++){
		for (int y = 0; y < rows; y++) {
			if (Array[y][x] == 0){
				suml += Array[y][x];
			}
			else
				suml += 1;
		}
	}

	cout << endl << "sum of left section:" << suml << endl;

	//sum center column 
	for (int x = 267; x < 533; x++) {
		for (int y = 0; y < rows; y++) {
			if (Array[y][x] == 0){
				suml += Array[y][x];
			}
			else
				suml += 1;
		}
	}

	cout << endl << "sum of center section:" << sumc << endl;

	//sum right column 
	for (int x = 533; x < 800; x++) {
		for (int y = 0; y < rows; y++) {
			if (Array[y][x] == 0){
				suml += Array[y][x];
			}
			else
				suml += 1;
		}
	}

	cout << endl << "sum of right section:" << sumr << endl;

	//compare results, choose direction

	if (sumc > (suml + 3) && suml <= sumr) {
		cout << "Turn left." << endl;
	}
	else if (sumc > (sumr + 3) && sumr < suml) {
		cout << "Turn right." << endl;
	}
	else
		cout << "Continue forward." << endl;

	return;
}




int main(int argc, char **argv)
{

	createTrackbars();
	on_trackbar(0, 0);

	Mat frame, blurred, thresimg, gray, canny, canny2;
	//frame = imread("images/testBMP2.bmp", CV_LOAD_IMAGE_UNCHANGED);	//	use threshval = 43
	frame = imread("rv.jpg", CV_LOAD_IMAGE_GRAYSCALE);	
	
	imwrite("gray.jpg", frame);

	//GaussianBlur(frame, blurred, Size(1011, 35), 1.5, 1.5);
	blur(frame, blurred, Size(40, 4));
	
	imwrite("blurred.jpg", blurred);
	

	Canny(blurred, canny, 50, 120, 3);
	
	imwrite("canny.jpg", canny);
	//cvtColor(blurred, gray, CV_BGR2GRAY);
	
	
		/* 0: Binary
		1: Binary Inverted
		2: Threshold Truncated
		3: Threshold to Zero
		4: Threshold to Zero Inverted
		*/
	threshold(blurred, thresimg, threshval, 255, CV_THRESH_BINARY_INV);
	imwrite("thresh.jpg", thresimg);
		
	imshow("Canny", canny);
	imshow("Threshing", thresimg);
		
	imshow("Blurred", blurred);
	imshow("Grayscale", frame);
		



fstream outputFile;
outputFile.open( "file.csv", ios::out ) ;

for(int i=0; i<canny.rows; i++)
{
    for(int j=0; j<canny.cols; j++)
    {
        outputFile << canny.at<float>(i,j) << ",";
    }
    outputFile << endl;

}
outputFile.close( );

fstream outputFile2;
outputFile2.open( "file2.csv", ios::out ) ;

for(int i=0; i<thresimg.rows; i++)
{
    for(int j=0; j<thresimg.cols; j++)
    {
        outputFile2 << thresimg.at<float>(i,j) << ",";
    }
    outputFile2 << endl;

}


//start of obstacle avoidance section
ifstream infile;


int Image_Array[Width][Height];

	infile.open("file2.csv");
	if (infile.is_open()) {
		cout << "file opened. \n";
			for (int row = 0; row < Width; ++row){
				string line;
				getline(infile, line);
				if( !infile.good())
					break;

				stringstream iss(line);
				for (int col = 0; col < Height; ++col){
					string val;
					getline(iss, val, ',');
					if( !iss.good())
						break;

					stringstream convert(val);
					convert >> Image_Array[row][col];
					//if(Image_Array[row][col] != '0')
						//Image_Array[row][col] = 1;
				}		
			}
		infile.close();
	}
	else {
		cout << "file wasn't opened.\n";
	}


/*
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
*/
	Analyze(Image_Array, Width, Height);



outputFile2.close( );
	waitKey(0);
}

void createTrackbars()
{
	namedWindow("Image", WINDOW_NORMAL);//create window trackbarwindow
	createTrackbar("Threshme", "Image", &threshval, 255, on_trackbar);
}
void createTrackbars2()
{
	namedWindow("Image", WINDOW_NORMAL);//create window trackbarwindow
	createTrackbar("Threshme", "Image", &threshval, 255, on_trackbar);
}

void on_trackbar(int, void*)
{//This function gets called whenever a
 // trackbar position is changed
	cout << threshval << endl;
}
