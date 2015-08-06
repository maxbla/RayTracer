#include <math.h>
#include <vector>
#include <cstdio>
#include "Camera.h"
#include "Sphere.h"
#include "simpleImage.h"
#include "Eigen/Dense"


int main (void) {
  int xRes = 500;
  int yRes = 500;
  double xHeight = 1.0;
  double yHeight = 1.0;
  double maxDist = 10.0;
  double sphereDistance = 4.0;
  double sphereRadius = 2.0;
  RGBColor sphereColor = RGBColor(0.0,1.0,0.5);
  RGBColor bgColor = RGBColor(0.2,0.2,0.2);
  SimpleImage img = SimpleImage(xRes, yRes, bgColor);
  Eigen::Vector4d sphereCenter = Eigen::Vector4d(0.0,0.0,sphereDistance,0.0);
  Eigen::Vector4d eyepoint = Eigen::Vector4d(0.0,0.0,-1.0,0.0);

  Sphere _sphere(sphereCenter, sphereRadius, sphereColor);
  Camera cam(maxDist, xRes, yRes, xHeight, yHeight, eyepoint);

  for (int localx = 0; localx<xRes; localx++){
    for (int localy = 0; localy<yRes; localy++){
      Ray n = cam.ShootRay(localx, localy);
      double result = _sphere.intersect(n);
      if (result >=0){
        RGBColor pointCol = _sphere.color;
        img.set(localx, localy, pointCol);
      }
    }
  }

  img.save("output.png");

  return 0;
}
