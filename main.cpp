#include <math.h>
#include <vector>
#include <cstdio>
#include "Camera.h"
#include "Sphere.h"
#include "Plane.h"
#include "simpleImage.h"
#include "Eigen/Dense"
#include "Eigen/Geometry"
#include <vector>
#include <algorithm>
#include <time.h>

  static std::vector< std::vector<double> > make2DArray (int xWidth, int yWidth, double initValue) {
    std::vector<std::vector<double> > arr(xWidth, std::vector<double>(yWidth, initValue));
    return arr;
  }

int main (void) {
  //get start time
  clock_t time = clock();

  //camera parameters
  int xRes = 1440;
  int yRes = 1440;
  double xHeight = 1.75;
  double yHeight = 1.75;
  double maxDist = 100.0;
  Eigen::Vector4d eyepoint = Eigen::Vector4d(0.0,0.0,-1.0,0.0);
  Eigen::Vector4d viewingDir = Eigen::Vector4d(0.0,0.0,1.0,0.0);
  Eigen::Vector4d upDir = Eigen::Vector4d(0.0,1.0,0.0,0.0);

  //sphere parameters
  double sphereRadius = 2.0;
  RGBColor sphereColor1 = RGBColor(0.5,1.0,0.5);
  RGBColor sphereColor2 = RGBColor(1.0,0.5,0.5);
  RGBColor bgColor = RGBColor(0.2,0.2,0.2);
  Eigen::Vector4d sphereCenter1 = Eigen::Vector4d(-2.0,2.0,7.0,0.0);
  Eigen::Vector4d sphereCenter2 = Eigen::Vector4d(4.0,1.5,7.0,0.0);
  double shine = 0.5;

  //plane parameters
  auto point1 = Eigen::Vector4d(0.0,-3.0,10.0,1.0);
  auto normal1 = Eigen::Vector4d(0.0,1.0,0.0,0.0);
  auto point2 = Eigen::Vector4d(0.0,0.0,15.0,1.0);
  auto normal2 = Eigen::Vector4d(0.0,0.0,-1.0,0.0);
  RGBColor planeColor = RGBColor(0.9,0.9,0.9);

  //initalize stuff
  SimpleImage img = SimpleImage(xRes, yRes, bgColor);
  Sphere _sphere1(sphereCenter1, sphereRadius, sphereColor1,shine);
  Sphere _sphere2(sphereCenter2, sphereRadius, sphereColor2,shine);
  Plane _plane1(point1,normal1,planeColor);
  Plane _plane2(point2,normal2,planeColor);
  Camera cam(maxDist, xRes, yRes, xHeight, yHeight, eyepoint, viewingDir, upDir);
  std::vector<std::vector<double> > depthBuffer = make2DArray (xRes,yRes,-1.0);
  std::vector<Surface*> surfaces;
  AreaLight light(Eigen::Vector4d(-2.0,5.0,2.0,1.0),RGBColor(1.0,1.0,1.0),1.0);

  surfaces.push_back(&_sphere1);
  surfaces.push_back(&_sphere2);
  surfaces.push_back(&_plane1);
  //surfaces.push_back(&_plane2);

  for (int pixelX = 0; pixelX<xRes; pixelX++){
    for (int pixelY = 0; pixelY<yRes; pixelY++){
      Ray n = cam.ShootRay(pixelX, pixelY);
      for (int i = 0; i<surfaces.size(); i+=1) {
        //std::cout<<surfaces.at(i).color.r<<' '<<surfaces.at(i).color.g<<' '<<surfaces.at(i).color.b<<std::endl;
        double result = surfaces[i]->intersect(n);
        //result is positive means an intersection has happened
        // result < delpthBuffer happens when new closer object is drawn in front of old one
        // delpthBuffer < -.9 happens when the depth buffer was formerly empty (it is initalized to -1.0)
        if (result >=0 && ((result < depthBuffer[pixelX][pixelY]) || (depthBuffer[pixelX][pixelY] < -.9))) {
          RGBColor imgColor = surfaces[i]->shade(n,result,light,surfaces)*(1.0-surfaces[i]->shine);
          if (surfaces[i]->shine > 0.01)
            imgColor = imgColor + surfaces[i]->reflect(n,result,light,surfaces,1)*(surfaces[i]->shine);
          img.set(pixelX, pixelY, imgColor);
          depthBuffer[pixelX][pixelY] = result;
        }
      }
    }
  }
  img.save("output.png");

  time = clock()-time;
  double millisecs = time/(CLOCKS_PER_SEC/1000);
  std::cout<<millisecs<<std::endl;

  return 0;
}
