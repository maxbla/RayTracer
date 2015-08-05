#include "Surface.h"
#include "Eigen/Dense"
#include "Ray.h"

class Sphere: public Surface {
public:
  Eigen::Vector4d center;
  double radius;

  Sphere(Vector4d center, double radius) {
    this->center = center;
    this->radius = radius;
  }



};
