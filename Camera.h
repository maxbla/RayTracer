#include "Eigen/Dense"
#include <vector>
#include <algorithm>
#include "simpleImage.h"
using namespace Eigen;

class Ray;

class Camera {
  public:
    double maxDist;
    int xRes;
    int yRes;
    double xHeight;
    double yHeight;
    double distance;
    Vector4d eyepoint;

    Camera(double _maxDist, int _xRes, int _yRes, double _xHeight, double _yHeight,
      double _distance, Vector4d _eyepoint);

    Camera();

    //returns a ray with world coordinates coresponding to pixel coordinates xPixel and yPixel (0,0 in top left)
    Ray ShootRay(int xPixel, int yPixel);
  };
