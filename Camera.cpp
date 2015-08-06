#include "Camera.h"
#include "Ray.h"
using namespace Eigen;
/*
    double maxDist;
    int xRes;
    int yRes;
    double xHeight;
    double yHeight;
    double distance;
    Vector4d eyepoint;
*/
    Camera::Camera(double _maxDist, int _xRes, int _yRes, double _xHeight, double _yHeight,
      double _distance, Vector4d _eyepoint) {
        xRes = _xRes;
        yRes = _yRes;
        xHeight = _xHeight;
        yHeight = _yHeight;
        distance = _distance;
        eyepoint = _eyepoint;
        maxDist = _maxDist;
      }

    Camera::Camera(){
      maxDist = 0.0;
      xRes = 0;
      yRes = 0;
      xHeight = 0.0;
      yHeight = 0.0;
      distance = 0.0;
      eyepoint = Vector4d(0.0,0.0,0.0,0.0);
    }

    Ray Camera::ShootRay(int xPixel, int yPixel) {
      double xWorld = xPixel*(xHeight/xRes)-xHeight/2;
      double yWorld = yPixel*(-yHeight/yRes)+yHeight/2;
      return Ray(0,100,eyepoint,Vector4d(eyepoint. xWorld,yWorld);
    }
