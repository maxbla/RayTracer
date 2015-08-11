#include "Eigen/Dense"
#include <vector>
#include <algorithm>
#include "simpleImage.h"

class Ray {
public:

  double start;
  double end;
  Eigen::Vector4d e;
  Eigen::Vector4d d;

  static void normalize(Ray &r) {
    double factor = sqrt(pow(r.d[0],2)+pow(r.d[1],2)+pow(r.d[2],2)+pow(r.d[3],2));
    r.d/= factor;
  }

  void normalize() {
    Ray::normalize(*this);
  }

  Ray(double _start, double _end, Eigen::Vector4d _e, Eigen::Vector4d _d) {
    start = _start;
    end = _end;
    e = _e;
    d = _d;
    normalize();
  }

  Ray() {
    start = 0.0;
    end = 1.0;
    e=Eigen::Vector4d(0,0,0,0);
    d=Eigen::Vector4d(0,0,1.0,0);
  }
};
