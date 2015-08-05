#include "Surface.h"
#include "Eigen/Dense"

class Sphere: public Surface {
public:
  Vector4d center;
  double radius;

  Sphere(Vector4d center, double radius) {
    this->center = center;
    this->radius = radius;
  }

  

}
