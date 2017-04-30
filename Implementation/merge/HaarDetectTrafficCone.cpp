#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace cv;

/** Function Headers */
int selectQuintant(int frameSize, int target);
int detectAndDisplay(Mat frame);
bool isOrange(Mat frame, Rect cone);

/** Global variables */
CascadeClassifier cone_cascade;
string window_name = "Capture - Traffic Cone Detection";

/** @function main */
int main(int argc, const char** argv)
{
	VideoCapture capture(0);
	Mat frame;
	int quintant;

	//-- 1. Load the cascade 
	if (!cone_cascade.load("HaarClassifier17Stage/cascade.xml")) {
		printf("--(!)Error loading\n");
		return -1;
	};

	while (1) {
		capture >> frame; 
		if (frame.empty()) {
			printf(" --(!) No captured frame -- Break!");
			break;
		}

		//-- 3. Apply the classifier to the frame
		quintant = detectAndDisplay(frame);

		if (quintant)
			cout << "Cone is in quintant: " << quintant << endl;

		int c = waitKey(10);
		if ((char)c == 27) { break; } // escape
	}
	waitKey(0);
}
/** @function detectAndDisplay */
int detectAndDisplay(Mat frame) {
	std::vector<Rect> cones;
	Mat gray;
	int quintant = 0;

	cvtColor(frame, gray, COLOR_BGR2GRAY);
	equalizeHist(gray, gray);

	//-- Detect cones
	cone_cascade.detectMultiScale(gray, cones, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

	if (cones.size() != 1)
		return 0;

	if (!isOrange(frame, cones[0])) {
		return 0;
	}

	rectangle(frame, Point(cones[0].x, cones[0].y), Point(cones[0].x + cones[0].width, cones[0].y + cones[0].height), Scalar(255, 255, 255), 2, 8);
	Point target(cones[0].x + cones[0].width / 2, cones[0].y + cones[0].height * 0.8);
	circle(frame, target, 3, Scalar(101, 255, 0), -1, 8);

	imshow("FRAME", frame);

	return selectQuintant(frame.size().width, target.x);
}
/** @function isOrange */
bool isOrange(Mat original, Rect cone) {
	Mat HSV;
	int xVal = cone.x + cone.width / 2;
	int yVal[3] = { 
		cone.y + cone.height*0.8, 
		cone.y + cone.height*0.2, 
		cone.y + cone.height*0.5 
	};
	
	for (int i = 0; i < sizeof(yVal)/sizeof(*yVal); ++i) {
		Mat RGB = original(Rect(xVal, yVal[i], 1, 1));
		cvtColor(RGB, HSV, CV_BGR2HSV);
		Vec3b hsv = HSV.at<Vec3b>(0, 0);
		int H = hsv.val[0];		//	Hue
		int S = hsv.val[1];		//	Saturation
		int V = hsv.val[2];		//	Value

		if (H < 180 && S > 39 && V > 234)
			return true;
	}
	return false;
}
/** @function selectQuintant */
int selectQuintant(int frameSize, int target) {
	if (target < .2 * frameSize)
		return 1;
	else if (target < .4 * frameSize)
		return 2;
	else if (target < .6 * frameSize)
		return 3;
	else if (target < .8 * frameSize)
		return 4;
	else
		return 5;
}
