/* This script calculates distance and bearing between two given coordinates. Yet we don't know the finishing pole coordinate, I just hard coded the coordinates
** of Black Rock, NV 40.753833, -119.275000 in the code 
** The main math formula for this code is using the Haversine Formula (from R.W. Sinnott, "Virtues of the Haversine", Sky and Telescope, vol. 68, no. 2, 1984, p. 159)
** Source: http://www.movable-type.co.uk/scripts/latlong.html
** 
*/
#include<iostream>
#include <math.h>
#include <iomanip>
#include <unistd.h>
#include <stdlib.h>


double PI= 3.14159265358979323846;
double radEarth = 6370009; //radians of earth in meters
double degreetoRadian(double deg){
  return deg * PI / 180;
}

double radiantoDegree(double rad){
  return rad * 180 / PI;
}

double calcDist(double currLat,double destLat, double currLong, double destlong){
  double dclat, ddlat;
  dclat = degreetoRadian(currLat); 
  ddlat = degreetoRadian(destLat); 
  double difLat = ddlat - dclat;
  double difLong = degreetoRadian(destlong-currLong); 
  double a = sin(difLat/2) * sin(difLat/2) + cos(dclat) * cos(ddlat) * sin(difLong/2) * sin(difLong/2);
 // double c = 2 * atan2(sqrt(a), sqrt(1-a)); 

  double c = 2 * asin(sqrt(a));

  double d = radEarth * c; 
  return d;
}

double calcBearing(double currLat, double destLat, double currLong, double destlong){
  double dclat = degreetoRadian(currLat);
  double ddlat = degreetoRadian(destLat);
  double difLong = degreetoRadian(destlong-currLong);
  double y = sin(difLong) * cos(destLat);
  double x = cos(currLat) * sin(destLat) - sin(currLat) * cos(destLat) * cos(difLong);
  double bearing = radiantoDegree(atan2(y,x)); 
  double compassNormalized = fmod(bearing - 360, 360); 
  return compassNormalized;
}

#ifndef Cube_h
#define Cube_h


double calcDist(double currLat,double destLat, double currLong, double destlong);
double calcBearing(double currLat, double destLat, double currLong, double destlong);

#endif


int main (){
using namespace std;
	
	double	currLat = 40.753820, destlat = 40.753833, currLong = -119.223000, destlong = -119.277000;

  std::cout << std::setprecision(11) << "(" << currLat << "," << currLong << ") --- ""(" << destlat << "," << destlong << ")\n";

  double compassNormalized = calcBearing(currLat, destlat, currLong, destlong);
  cout << "Initial heading =  " << compassNormalized << endl;

  double d = calcDist(currLat, destlat, currLong, destlong);
  cout << "distance to travel = " << d << endl;
  

}

void navigation(double currLat, double currLong, double destLat, double destlong)
{
 if(calcDist(currLat, destLat, currLong, destlong) < 2)
	 sleep(5);
 else
 {
   calcBearing(currLat, destLat, currLong, destlong);
   //roverforward();
 }
}