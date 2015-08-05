#include <cmath>
#include <cstdio>
#include "Ray.h"
#include "Camera.h"
#include "Surface.h"
#include "Sphere.h"
#include "simpleImage.h"
#include "Eigen/Dense"


int main (void) {
  double maxDist = 10f;
  int xRes = 500;
  int yRes = 500;
  double xHeight = 1f;
  double yHeight = 1f;
  double distance = 1f;
  Vector4d eyepoint = (0f,0f,-distance);
  Camera new = Camera(maxDist, xRes, yRes, xHeight, yHeight, distance, eyepoint);
}
