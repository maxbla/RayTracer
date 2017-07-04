#include "AreaLight.h"

AreaLight::AreaLight() : 
	radius(1.0) 
{
	Light(Eigen::Vector4d(0.0,0.0,0.0,1.0), RGBColor(1.0,1.0,1.0)); 
}

AreaLight::AreaLight(Eigen::Vector4d location, RGBColor color) {
    this->location = location;
    this->color = color;
    radius = 1.0;
  }

AreaLight::AreaLight(Eigen::Vector4d location, RGBColor color, double radius) {
    this->location = location;
    this->color = color;
    this->radius = radius;
  }
Eigen::Vector4d AreaLight::Sample(int totalSamples, int sampleNumber) {
    int samplesPerRow = (int)(sqrt((double)totalSamples)+.1);
    int rowNumber = sampleNumber / samplesPerRow;
    int columnNumber = sampleNumber % samplesPerRow;
    float xDif = 2.0*(rowNumber/((double)samplesPerRow)-0.5);
    float yDif = 2.0*(columnNumber/((double)samplesPerRow)-0.5);
    return location + Eigen::Vector4d(xDif,yDif,0.0,0.0);
  }
