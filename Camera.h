#include "Eigen/Dense"
#include <vector>
#include <algorithm>
#include "SimpleImage.h"
#include "Ray.h"

class Camera {
  public:
    //the maximum distance from the camera that is rendered
    double maxDist;
    //the number of pixels in the x direction (in image space)
    int xRes;
    //the number of pixels in the y direction (in image space)
    int yRes;
    //the width of the image plane in world space
    double xHeight;
    //the height of the image plane in world space
    double yHeight;
    //the vector that represents the up direction for the camera
    Eigen::Vector4d upDirection;
    //the direction that the central viewing ray travels in
    Eigen::Vector4d direction;
    //the third driection, which is the positive x direction in image space
    Eigen::Vector4d positiveX;
    //the eyepoint of the camera
    Eigen::Vector4d eyepoint;

    Camera(double _maxDist, int _xRes, int _yRes, double _xHeight, double _yHeight,
      Eigen::Vector4d _eyepoint, Eigen::Vector4d _direction, Eigen::Vector4d _upDirection);

    Camera(double _maxDist, int _xRes, int _yRes, double _xHeight, double _yHeight,
      Eigen::Vector4d _direction, Eigen::Vector4d _eyepoint);

    Camera(double _maxDist, int _xRes, int _yRes, double _xHeight, double _yHeight,
      Eigen::Vector4d _eyepoint);

    Camera();

    Eigen::Vector4d cross4d(Eigen::Vector4d dir1, Eigen::Vector4d dir2);

    //returns a ray with world coordinates coresponding to pixel coordinates xPixel and yPixel (0,0 in top left)
    Ray ShootRay(int xPixel, int yPixel);
  };
