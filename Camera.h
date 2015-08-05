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
      maxDist = 0f;
      xRes = 0;
      yRes = 0;
      xHeight = 0f;
      yHeight = 0f;
      distance = 0f;
      eyepoint = Vector4d(0f,0f,0f,0f);
    }
    ShootRay()
  }
