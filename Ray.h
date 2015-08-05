#include "Eigen/Dense"
#include <vector>
#include <algorithm>
#include "simpleImage.h"


struct Ray {

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
    start = 0f;
    end = 1f;
    e=Vector4d(0,0,0,0);
    d=Vector4d(0,0,0,0);
  }
}
