#include "Eigen/Dense"
#include <vector>
#include <algorithm>
#include "simpleImage.h"
#include "Ray.h"

class Camera {
  public:
    double maxDist;
    int xRes;
    int yRes;
    double xHeight;
    double yHeight;
    Eigen::Vector4d upDirection;
    Eigen::Vector4d direction;
    Eigen::Vector4d eyepoint;

    Camera(double _maxDist, int _xRes, int _yRes, double _xHeight, double _yHeight,
      Eigen::Vector4d _direction, Eigen::Vector4d _eyepoint);

    Camera(double _maxDist, int _xRes, int _yRes, double _xHeight, double _yHeight,
      Eigen::Vector4d _eyepoint);

    Camera();

    //returns a ray with world coordinates coresponding to pixel coordinates xPixel and yPixel (0,0 in top left)
    Ray ShootRay(int xPixel, int yPixel);
  };
