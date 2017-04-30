#include "main.h"

using namespace std;
using namespace cv;

Finish::Finish (MotorFuncs* m) {
	fieldOfView = 90.0;   //View angle of camera for course correction
	waitTime = 2.0;       //Time to wait between course corrections
	srand(time (NULL));   //Seed random number generator for testing

	//Load the Cascade Classifier for the cone
	if (!cone_cascade.load("HaarClassifier17Stage/cascade.xml")) {
	    printf("ERROR: Unable to load Cone Classifier\n");
	};

	
	myMotors = m;
}

void Finish::touchPole () {

	bool foundPole = false;     //Set to true once pole is found
	bool poleInView = true;     //Set to false once pole is out of view
	int sector = 0;             //Sector of image pole is located

	printf ("Testing Find and Touch Finish Pole Module:\n");
	printf ("View Angle: %f\nWait Time: %f\n", fieldOfView, waitTime);
	
	//Rotate and take picture until finding pole
	while (! foundPole) {
		if (! findPole ()) {
			printf ("Did not find pole.\n");
			myMotors->roverRotate (10.);
		}
		else {
			printf ("Did find pole.\n");
			foundPole = true;
		}
	}

	//Head towards the pole until hitting it.
	while (poleInView) {
		myMotors->roverForward ();
		sleep (waitTime);
		myMotors->roverStop ();
		
		sector = findPole ();
		if (sector) {
			//Rotate rover by proportion of view angle of camera
			myMotors->roverRotate ((fieldOfView / 5.0) * (sector - 3));
		}
		else {
			printf ("Pole no longer in view.\n");
			poleInView = false;
		}
	}
	//Continue forward since pole is close enough to not be seen by camera
	myMotors->roverForward ();
	printf ("Hit Pole\n");
}

int Finish::findPole () {
	/*
	  This function utilizes the camera to find the pole.
	  If the pole is in the image, the function returns the
	  sector of the image it's in (1-5), else returns 0
	*/
	if (!DEBUG) {
		Mat frame;
		VideoCapture capture(0);
	
		capture >> frame;
		return detectAndDisplay (frame);
	}
	else {
		//Simulate functionality without camera
		return rand() % 6;
	}
}

/** @function detectAndDisplay */
int Finish::detectAndDisplay(Mat frame) {
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
bool Finish::isOrange(Mat original, Rect cone) {
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
int Finish::selectQuintant(int frameSize, int target) {
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
