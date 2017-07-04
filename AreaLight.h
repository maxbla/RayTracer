#include "Light.h"
#include "SimpleImage.h"
#include "Eigen/Dense"

#ifndef AREA_LIGHT_H_
#define AREA_LIGHT_H_
/*a spherical 'area' (volume) light*/
class AreaLight: public Light {
public:
	AreaLight();
	AreaLight(Eigen::Vector4d location, RGBColor color);
	AreaLight(Eigen::Vector4d location, RGBColor color, double radius);
	Eigen::Vector4d Sample(int totalSamples, int sampleNumber);
	double radius;


/*
  Eigen::Vector4d Sample(int n) {
    time_t time = clock();
    double nanosecs = time/(CLOCKS_PER_SEC/1000000);
    srand(nanosecs);
    double randomDist = (rand()%101)/100.0*radius;
    //std::cout <<randomDist<<std::endl;
    auto direction = Eigen::Vector4d(rand(),rand(),0.0,0.0);
    direction.normalize();
    return location + direction * randomDist;
  }
  */


//Eigen::Vector4d randomSample() {return location;}
};


#endif
