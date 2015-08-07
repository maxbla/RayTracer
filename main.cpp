#include <math.h>
#include <vector>
#include <cstdio>
#include "Camera.h"
#include "Sphere.h"
#include "simpleImage.h"
#include "Eigen/Dense"
#include <vector>

  static std::vector< std::vector<double> > make2DArray (int xWidth, int yWidth, double initValue) {
    std::vector<std::vector<double> > arr(xWidth, std::vector<double>(yWidth, initValue));
    return arr;
  }

int main (void) {
  int xRes = 500;
  int yRes = 500;
  double xHeight = 1.0;
  double yHeight = 1.0;
  double maxDist = 10.0;
  double sphereDistance = 7.0;
  double sphereRadius = 2.0;
  RGBColor sphereColor1 = RGBColor(0.0,1.0,0.5);
  RGBColor sphereColor2 = RGBColor(1.0,0.0,0.5);
  RGBColor bgColor = RGBColor(0.2,0.2,0.2);
  SimpleImage img = SimpleImage(xRes, yRes, bgColor);
  Eigen::Vector4d sphereCenter1 = Eigen::Vector4d(0.0,-1.0,sphereDistance,0.0);
  Eigen::Vector4d sphereCenter2 = Eigen::Vector4d(1.0,1.0,sphereDistance+1.0,0.0);
  Eigen::Vector4d eyepoint = Eigen::Vector4d(0.0,0.0,-1.0,0.0);

  Sphere _sphere1(sphereCenter1, sphereRadius, sphereColor1);
  Sphere _sphere2(sphereCenter2, sphereRadius, sphereColor2);
  Camera cam(maxDist, xRes, yRes, xHeight, yHeight, eyepoint);
  std::vector<std::vector<double> > depthBuffer = make2DArray (xRes,yRes,-1.0);

  for (int localx = 0; localx<xRes; localx++){
    for (int localy = 0; localy<yRes; localy++){
      Ray n = cam.ShootRay(localx, localy);
      double result = _sphere1.intersect(n);
      //result is positive means an intersection has happened
      // result < delpthBuffer happens when new closer object is drawn in front of old one
      // delpthBuffer < -.9 happens when the depth buffer was formerly empty (it is initalized to -1.0)
      if (result >=0 && ((result < depthBuffer[localx][localy]) || (depthBuffer[localx][localy] < -.9))) {
        RGBColor pointCol = _sphere1.color;
        img.set(localx, localy, pointCol);
        depthBuffer[localx][localy] = result;
      }
    }
  }

  for (int localx = 0; localx<xRes; localx++){
    for (int localy = 0; localy<yRes; localy++){
      Ray n = cam.ShootRay(localx, localy);
      double result = _sphere2.intersect(n);
      //result is positive means an intersection has happened
      // result < delpthBuffer happens when new closer object is drawn in front of old one
      // delpthBuffer < -.9 happens when the depth buffer was formerly empty (it is initalized to -1.0)
      if (result >=0 && ((result < depthBuffer[localx][localy]) || (depthBuffer[localx][localy] < -.9))) {
        RGBColor pointCol = _sphere2.color;
        img.set(localx, localy, pointCol);
        depthBuffer[localx][localy] = result;
      }
    }
  }

  img.save("output.png");

  return 0;
}
