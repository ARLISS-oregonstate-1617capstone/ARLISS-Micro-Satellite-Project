#include "main.h"

using namespace cv;
using namespace std;

void on_trackbar(int, void*);

Obstacle::Obstacle (MotorFuncs* m) {

	threshval = 150;

	myMotors = m;
}

/*
  # The Analyze function is the heart of the obstacle avoidance module. this function takes in our image array, and then checks which
  # of the three columns (left, center, or right) has the fewest edges and then decides which direction to go based off that data.
  #
  #
*/
void Obstacle::Analyze(int(Array)[][Height], int rows, int cols) {

	int suml = 0, sumc = 0, sumr = 0;
	//sum left column 
	for (int x = 0; x < 360; x++){
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
	for (int x = 360; x < 720; x++) {
		for (int y = 0; y < rows; y++) {
			if (Array[y][x] == 0){
				suml += Array[y][x];
			}
			else
				sumc += 1;
		}
	}

	cout << endl << "sum of center section:" << sumc << endl;

	//sum right column 
	for (int x = 720; x < 1080; x++) {
		for (int y = 0; y < rows; y++) {
			if (Array[y][x] == 0){
				suml += Array[y][x];
			}
			else
				sumr += 1;
		}
	}

	cout << endl << "sum of right section:" << sumr << endl;

	//compare results, choose direction ------------ modify to account for larger values

	if (sumc > (suml + 3) && suml <= sumr) {
		cout << "Turn left." << endl;
		myMotors->roverRotate (-30.);
	}
	else if (sumc > (sumr + 3) && sumr < suml) {
		cout << "Turn right." << endl;
		myMotors->roverRotate (30.);
	}
	else
		cout << "Continue forward." << endl;

	return;
}




void Obstacle::checkObstacle()
{

	createTrackbars();
	on_trackbar(0, 0);

	Mat frame, blurred, thresimg, gray, canny, canny2;
	//frame = imread("images/testBMP2.bmp", CV_LOAD_IMAGE_UNCHANGED);
	//use threshval = 43

	if (!DEBUG) {
		//Capture frame from camera
		VideoCapture capture(0);
		capture >> frame;
	}
	else {
		//Use test image as frame
		frame = imread("road.jpg", CV_LOAD_IMAGE_GRAYSCALE);	
	}
	
	//imwrite("gray.jpg", frame);

	//GaussianBlur(frame, blurred, Size(1011, 35), 1.5, 1.5);
	blur(frame, blurred, Size(40, 4));
	
	//imwrite("blurred.jpg", blurred);
	

	Canny(blurred, canny, 50, 120, 3);
	
	//imwrite("canny.jpg", canny);
	//cvtColor(blurred, gray, CV_BGR2GRAY);
	
	
	/* 0: Binary
	   1: Binary Inverted
	   2: Threshold Truncated
	   3: Threshold to Zero
	   4: Threshold to Zero Inverted
	*/
	threshold(blurred, thresimg, threshval, 255, CV_THRESH_BINARY_INV);
	//imwrite("thresh.jpg", thresimg);
		
	//imshow("Canny", canny);
	//imshow("Threshing", thresimg);
		
	//imshow("Blurred", blurred);
	//imshow("Grayscale", frame);
		
	int Image_Array[Width][Height];
 
	for(int i=0; i<canny.rows; i++)
		{
			for(int j=0; j<canny.cols; j++)
				{
					Vec3b color = canny.at<Vec3b>(Point(j,i));
					if(color.val[0] >= 25 && color.val[1] >= 25 && color.val[2] >= 25) {
						Image_Array[j][i] = 1;
					}
					else {
						Image_Array[j][i] = 0;
					}
				}
		}
	//start of obstacle avoidance section

	Analyze(Image_Array, Width, Height);

}

void Obstacle::createTrackbars()
{
	namedWindow("Image", WINDOW_NORMAL);//create window trackbarwindow
	createTrackbar("Threshme", "Image", &threshval, 255, on_trackbar);
}
void Obstacle::createTrackbars2()
{
	namedWindow("Image", WINDOW_NORMAL);//create window trackbarwindow
	createTrackbar("Threshme", "Image", &threshval, 255, on_trackbar);
}

void on_trackbar(int, void*)
{//This function gets called whenever a
 // trackbar position is changed
	cout << "Changing theshval" << endl;
}
