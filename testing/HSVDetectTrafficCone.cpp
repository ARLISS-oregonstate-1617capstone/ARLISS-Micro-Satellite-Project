#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace cv;

/** Function Headers */
void filterFrame(Mat original);
int selectQuintant(int frameSize, int target);
double convexHullPointsUp(vector<vector<Point> >&cone, vector<Point> hull, Rect rect);
void displayResult(Mat original, vector<vector<Point> >cone, Point target);

/** @function main */
int main(int argc, const char** argv)
{
	VideoCapture capture(0);
	Mat frame;

	//frame = imread("images (27).jpg", IMREAD_COLOR);

	while(1)
	{
		capture >> frame;
		if (frame.empty())
		{
			printf(" --(!) No captured frame -- Break!");
			break;
		}

		//-- 3. Apply the classifier to the frame
		filterFrame(frame);

		int c = waitKey(10);
		if ((char)c == 27) { break; } // escape

	}
	waitKey(0);
}

void filterFrame(Mat original) {
	Mat HSV, thresh, thresh_lower, thresh_upper, smoothed, canny;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	cvtColor(original, HSV, CV_BGR2HSV);
	inRange(HSV, Scalar(0, 40, 235), Scalar(179, 255, 255), thresh_lower);
	inRange(HSV, Scalar(159, 140, 211), Scalar(179, 255, 255), thresh_upper);
	addWeighted(thresh_lower, 1.0, thresh_upper, 1.0, 0.0, thresh);

	imshow("Thresh", thresh);

	//	Morphological opening (remove small objects from the foreground)
	erode(thresh, thresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(thresh, thresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	//	Morphological closing (fill small holes in the foreground)
	dilate(thresh, thresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(thresh, thresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//GaussianBlur(thresh, smoothed, Size(9, 9), 1, 1);
	Canny(thresh, canny, 80, 160, 3);

	//	Find contours
	findContours(canny, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_L1, Point(0, 0));

	//	Find convex hulls
	vector<vector<Point> >hull(contours.size());
	for (int i = 0; i < contours.size(); i++)
		convexHull(Mat(contours[i]), hull[i], true);

	//	Finds which convex hulls are pointed up
	vector<vector<Point> >cone(contours.size());
	vector<Rect> boundRect(contours.size());
	Point target;
	double maxArea = 0;
	for (int i = 0; i < hull.size(); ++i) {
		Rect rect = boundingRect(Mat(hull[i]));
		//	Finds center of largest piece of the cone
		int currentArea = convexHullPointsUp(cone, hull[i], rect);
		if (currentArea > maxArea) {
			maxArea = currentArea;
			target.x = rect.x + (rect.width / 2);
			target.y = rect.y + (rect.height * 0.8);
		}
	}

	/** Temporary code to display results **/
	displayResult(original, cone, target);
	imshow("HSV", HSV);
	imshow("Canny", canny);
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

/** @function convexHullPointsUp */
double convexHullPointsUp(vector<vector<Point> >&cone, vector<Point> hull, Rect rect) {
	int yCenter = rect.y + (rect.height / 2);
	double aspectRatio = rect.width / rect.height;
	
	//	If convex hull is not taller than it is wide
	if (aspectRatio > 1)
		return 0;

	vector<Point> pointsAboveCenter, pointsBelowCenter;
	for (int i = 0; i < hull.size(); ++i) {
		if (hull[i].y >= yCenter)
			pointsBelowCenter.push_back(hull[i]);
		if (hull[i].y < yCenter)
			pointsAboveCenter.push_back(hull[i]);
	}

	int LeftMostPoint = hull[0].x;
	int RightMostPoint = hull[0].x;
	for (int i = 0; i < pointsBelowCenter.size(); ++i) {
		if (pointsBelowCenter[i].x < LeftMostPoint)
			LeftMostPoint = pointsBelowCenter[i].x;
	}
	for (int i = 0; i < pointsBelowCenter.size(); ++i) {
		if (pointsBelowCenter[i].x > RightMostPoint)
			RightMostPoint = pointsBelowCenter[i].x;
	}
	for (int i = 0; i < pointsAboveCenter.size(); ++i) {
		if (pointsAboveCenter[i].x < LeftMostPoint || pointsAboveCenter[i].x > RightMostPoint)
			return 0;
	}

	cone.push_back(hull);
	return rect.width * rect.height;
}
/** @function displayResult */
void displayResult(Mat original, vector<vector<Point> >cone, Point target) {
	RNG rng(12345);
	// Draw cone results
	Mat drawing = Mat::zeros(original.size(), CV_8UC3);
	for (int i = 0; i < cone.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		if (cone[i].size() >= 10 && cone[i].size() <= 20) {
			drawContours(drawing, cone, i, color, 1, 8, vector<Vec4i>(), 0, Point());
			circle(drawing, target, 3, Scalar(255, 255, 255), -1, 8);
		}
	}
	imshow("Hull", drawing);
	cout << "Cone is in quintant: " << selectQuintant(original.size().width, target.x) << endl;
}
 
