#include "Light.h"
#include <stdlib.h> /*used for rand*/
#include <time.h>

/*a spherical 'area' (volume) light*/
class AreaLight: public Light {
public:
  double radius;

  AreaLight() {
    location = Eigen::Vector4d(0.0,0.0,0.0,1.0);
    color = RGBColor(1.0,1.0,1.0);
    radius = 1.0;
  }

  AreaLight(Eigen::Vector4d location, RGBColor color) {
    this->location = location;
    this->color = color;
    radius = 1.0;
  }

  AreaLight(Eigen::Vector4d location, RGBColor color, double radius) {
    this->location = location;
    this->color = color;
    this->radius = radius;
  }

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

  Eigen::Vector4d Sample(int totalSamples, int sampleNumber) {
    int samplesPerRow = (int)(sqrt((double)totalSamples)+.1);
    int rowNumber = sampleNumber / samplesPerRow;
    int columnNumber = sampleNumber % samplesPerRow;
    float xDif = 2.0*(rowNumber/((double)samplesPerRow)-0.5);
    float yDif = 2.0*(columnNumber/((double)samplesPerRow)-0.5);
    return location + Eigen::Vector4d(xDif,yDif,0.0,0.0);
  }

  Eigen::Vector4d randomSample() {return location;}
};
