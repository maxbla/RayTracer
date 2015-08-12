#include <math.h>
#include <vector>
#include <cstdio>
#include "Camera.h"
#include "Sphere.h"
#include "simpleImage.h"
#include "Eigen/Dense"
#include "Eigen/Geometry"
#include <vector>

  static std::vector< std::vector<double> > make2DArray (int xWidth, int yWidth, double initValue) {
    std::vector<std::vector<double> > arr(xWidth, std::vector<double>(yWidth, initValue));
    return arr;
  }

int main (void) {
  //camera parameters
  int xRes = 500;
  int yRes = 500;
  double xHeight = 1.0;
  double yHeight = 1.0;
  double maxDist = 10.0;
  Eigen::Vector4d eyepoint = Eigen::Vector4d(0.0,0.0,-1.0,0.0);
  Eigen::Vector4d viewingDir = Eigen::Vector4d(0.1,0.0,1.0,0.0);
  Eigen::Vector4d upDir = Eigen::Vector4d(0.0,1.0,0.0,0.0);

  //sphere parameters
  double sphereDistance = 7.0;
  double sphereRadius = 2.0;
  RGBColor sphereColor1 = RGBColor(0.0,1.0,0.5);
  RGBColor sphereColor2 = RGBColor(1.0,0.0,0.5);
  RGBColor bgColor = RGBColor(0.2,0.2,0.2);
  Eigen::Vector4d sphereCenter1 = Eigen::Vector4d(0.0,-1.0,sphereDistance,0.0);
  Eigen::Vector4d sphereCenter2 = Eigen::Vector4d(1.0,1.0,sphereDistance+1.0,0.0);

  //initalize stuff
  SimpleImage img = SimpleImage(xRes, yRes, bgColor);
  Sphere _sphere1(sphereCenter1, sphereRadius, sphereColor1);
  Sphere _sphere2(sphereCenter2, sphereRadius, sphereColor2);
  Camera cam(maxDist, xRes, yRes, xHeight, yHeight, eyepoint, viewingDir, upDir);
  std::vector<std::vector<double> > depthBuffer = make2DArray (xRes,yRes,-1.0);
  Surface* surfaces[10];
  int surfaceIndex = 0;

  surfaces[surfaceIndex++] = &_sphere1;
  surfaces[surfaceIndex++] = &_sphere2;

  for (int localx = 0; localx<xRes; localx++){
    for (int localy = 0; localy<yRes; localy++){
      Ray n = cam.ShootRay(localx, localy);
      for (int i = 0; i<surfaceIndex; i+=1) {
        //std::cout<<surfaces.at(i).color.r<<' '<<surfaces.at(i).color.g<<' '<<surfaces.at(i).color.b<<std::endl;
        double result = surfaces[i]->intersect(n);
        //result is positive means an intersection has happened
        // result < delpthBuffer happens when new closer object is drawn in front of old one
        // delpthBuffer < -.9 happens when the depth buffer was formerly empty (it is initalized to -1.0)
        if (result >=0 && ((result < depthBuffer[localx][localy]) || (depthBuffer[localx][localy] < -.9))) {
          img.set(localx, localy, surfaces[i]->color);
          depthBuffer[localx][localy] = result;
        }
      }
    }
  }

  img.save("output.png");

  return 0;
}
