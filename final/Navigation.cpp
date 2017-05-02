/* This script calculates distance and bearing between two given coordinates. Yet we don't know the finishing pole coordinate, I just hard coded the coordinates
** of Black Rock, NV 40.753833, -119.275000 in the code 
** The main math formula for this code is using the Haversine Formula (from R.W. Sinnott, "Virtues of the Haversine", Sky and Telescope, vol. 68, no. 2, 1984, p. 159)
** Source: http://www.movable-type.co.uk/scripts/latlong.html
** 
*/
#include "main.h"

using namespace std;

Navigation::Navigation (GPSFuncs* g, MotorFuncs* m) {
	destLat = 40.753820;
	destLong = -119.277000;
	roverHeading = 0;
	
	myGPS = g;
	myMotors = m;
}

double Navigation::degreetoRadian(double deg){
  return deg * M_PI / 180;
}

double Navigation::radiantoDegree(double rad){
  return rad * 180 / M_PI;
}

double Navigation::calcDist(double currLat, double currLong){
  double dclat, ddlat;
  double radEarth = 6370009; //radians of earth in meters
  dclat = degreetoRadian(currLat); 
  ddlat = degreetoRadian(destLat); 
  double difLat = ddlat - dclat;
  double difLong = degreetoRadian(destLong-currLong); 
  double a = sin(difLat/2) * sin(difLat/2) + cos(dclat) * cos(ddlat) * sin(difLong/2) * sin(difLong/2);

  double c = 2 * asin(sqrt(a));

  double d = radEarth * c; 
  return d;
}

double Navigation::initHeading(double preLat, double currLat, double preLong, double currLong){
  double difLong = degreetoRadian(currLong - preLong);
  double y = sin(difLong) * cos(currLat);
  double x = cos(preLat) * sin(currLat) - sin(preLat) * cos(currLat) * cos(difLong);
  double bearing = radiantoDegree(atan2(y,x)); 
  double roverInitialHeading = fmod(bearing - 360, 360); 
  return roverInitialHeading;
  
}

double Navigation::calcBearing(double currLat, double currLong){
  double difLong = degreetoRadian(destLong-currLong);
  double y = sin(difLong) * cos(destLat);
  double x = cos(currLat) * sin(destLat) - sin(currLat) * cos(destLat) * cos(difLong);
  double bearing = radiantoDegree(atan2(y,x)); 
  double compassNormalized = fmod(bearing - 360, 360); 
  return compassNormalized;
}

void Navigation::startNavigation (){
	double preLat = 0.;   
	double preLong = 0.;
	
	preLat = myGPS->getYCoord ();
	preLong = myGPS->getXCoord ();

	// rover move forward
	myMotors->roverForward (); 
	sleep (2);
	myMotors->roverStop ();
	
	double currLat = myGPS->getYCoord ();
	double currLong = myGPS->getXCoord ();
	
	std::cout << std::setprecision(11) << "(" << preLat << "," << preLong << ") --- ""(" << currLat << "," << currLong << ")\n";
	
	double roverInitialHeading = initHeading(preLat, currLat, preLong, currLong);
	cout << "Rover Initial heading =  " << roverInitialHeading << endl;
	
	std::cout << std::setprecision(11) << "(" << currLat << "," << currLong << ") --- ""(" << destLat << "," << destLong << ")\n";

    double compassNormalized = calcBearing(currLat, currLong);
    roverHeading = compassNormalized - roverInitialHeading;
    cout << "Rover heading to destination =  " << roverHeading << endl;
	
    double d = calcDist(currLat, currLong);
    cout << "distance to travel = " << d << endl;
  

}

void Navigation::navigation(double currLat, double currLong)
{
 if(calcDist(currLat, currLong) < 2)
	 sleep(5);
 else
 {
   calcBearing(currLat, currLong);
   calcDist(currLat, currLong);
   myMotors->roverRotate(roverHeading);
   myMotors->roverForward();
   
 }
}
