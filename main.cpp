#include <math.h>
#include <vector>
#include <cstdio>
#include "Camera.h"
#include "Sphere.h"
#include "simpleImage.h"
#include "Eigen/Dense"

int xRes = 500;
int yRes = 500;
double xHeight = 1f;
double yHeight = 1f;

int l2gx (double local){
  return int(-xHeight + local/xRes);
}

int l2gy (double local){
  return int(-yHeight + local/yRes);
}

int main (void) {
<<<<<<< Updated upstream
  double maxDist = 10.0;
  int xRes = 500;
  int yRes = 500;
  double xHeight = 1.0f;
  double yHeight = 1.0f;
  double distance = 1.0f;

  std::vector<Ray> allRays;
  double start = 0.0;
  double end = 3.0;
  double maxDist = 10.0;
  double distance = 1.0;
  Vector4d eyepoint = Vector4d(0.0,0.0,-distance,0.0);
  Camera new = Camera(maxDist, xRes, yRes, xHeight, yHeight, distance, eyepoint);
  for (double localx = 0; localx<xRes; localx++){
    for (double localy = 0; localy<yRes; localy++){
      globalx = l2gx(localx);
      globaly = l2gy(localy);
      Vector4d d = Vector4d(globalx,globaly,0.0,0.0);
      Ray n = Ray(start, end, eyepoint, d);
      allRays.push_back(n);
    }
  }
  for (std::vector<Ray>::iterator i = allRays.begin(); i!= allRays.end(); ++i){
    //get the intersection information
  }

>>>>>>> Stashed changes
}
