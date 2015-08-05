#include "Eigen/Dense"
#include <vector>
#include <algorithm>
#include "simpleImage.h"
using namespace Eigen;

class Ray {
public:

  double start;
  double end;
  Vector4d e;
  Vector4d d;

  Ray(double _start, double _end, Vector4d _e, Vector4d _d) {
    start = _start;
    end = _end;
    e = _e;
    d = _d;
      }

  Ray() {
    start = 0.0;
    end = 1.0;
    e=Vector4d(0,0,0,0);
    d=Vector4d(0,0,0,0);
  }
};
