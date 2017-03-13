#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>
//#include "opencv-3.2.0/modules/imgproc/include/opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv-3.2.0/modules/highgui/include/opencv2/highgui/highgui.hpp"
//#include "opencv-3.2.0/modules/core/include/opencv2/core/core.hpp"

using namespace cv;
using namespace std;

int threshval = 150;
void on_trackbar(int, void*);
void createTrackbars();

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
	
	//while (waitKey(30) != 27)
	//{	
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
		//ofstream outputFile("image.csv");
		//outputFile << format(thresimg, "CSV") << endl;
		//outputFile.close();
	//}
	//Mat gray, edge, draw;
	//cvtColor(thresimg, gray, CV_BGR2GRAY);
		/*std::vector<uchar> array;
		for (int i = 0; i < canny.rows; ++i) {
			int canny.
			if()
			array.insert(array.end(), mat.ptr<uchar>(i), mat.ptr<uchar>(i) + mat.cols);
		}*/

		/*std::vector<uchar> array;
		if (canny.isContinuous()) {
			array.assign(canny.datastart, canny.dataend);
		}
		else {
			for (int i = 0; i < canny.rows; ++i) {
				array.insert(array.end(), canny.ptr<uchar>(i), canny.ptr<uchar>(i) + canny.cols);
			}
		}
		for (const auto& i : array)
			std::cout << i << ' ';*/

	//imshow("image", gray);
	//imwrite("notBlurred.jpg", gray);



fstream outputFile;
outputFile.open( "file.csv", ios::out ) ;

for(int i=0; i<canny.rows; i++)
{
    for(int j=0; j<canny.cols; j++)
    {
        outputFile << canny.at<float>(i,j) << ", ";
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
        outputFile2 << thresimg.at<float>(i,j) << ", ";
    }
    outputFile2 << endl;

}
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
