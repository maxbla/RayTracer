#include "Camera.h"
#include "Ray.h"
using namespace Eigen;

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
      double _distance, Vector4d _eyepoint) {
        xRes = _xRes;
        yRes = _yRes;
        xHeight = _xHeight;
        yHeight = _yHeight;
        distance = _distance;
        eyepoint = _eyepoint;
        maxDist = _maxDist;
      }

    Camera(){
      maxDist = 0.0;
      xRes = 0;
      yRes = 0;
      xHeight = 0.0;
      yHeight = 0.0;
      distance = 0.0;
      eyepoint = Vector4d(0.0,0.0,0.0,0.0);
    }

    Ray ShootRay(int xPixel, int yPixel) {
      //placeholder return statement
      return Ray();
    }
  };
