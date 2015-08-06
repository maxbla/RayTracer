#include "Surface.h"
#include "Eigen/Dense"
#include "Ray.h"
#include <math.h>

class Sphere: public Surface {
public:
  //center of sphere
  Eigen::Vector4d c;
  //radius of sphere
  double rad;
  //color of sphere object
  RGBColor color;

  Sphere () {
    c = Vector4d(0.0,0.0,0.0,0.0);
    rad = 1.0;
    color = RGBColor(1.0,1.0,1.0);
  }

  Sphere(Vector4d center, double radius){
    c = center;
    rad = radius;
    color = RGBColor(1.0,1.0,1.0);
  }

  Sphere(Vector4d center, double radius, RGBColor color) {
    c = center;
    rad = radius;
    this->color = color;
  }

  /*returns the time value at the intersection of the ray and sphere*/
  double intersect(Ray r) {
    //calculate determinant of intersection equation
    double det = r.d.dot(r.e-c)*r.d.dot(r.e-c) -
    (r.d.dot(r.d))*((r.e-c).dot(r.e-c)-rad*rad);
    if (det < 0) {
      return -1;
    }
    else { //problem has 2 solutions
      //solution 1 where t = (-b + sqrt(det))/2a
      double sol1 = (sqrt(det) - r.d.dot(r.e-c))/(r.d.dot(r.d));
      //solution 2 where t = -(b + sqrt(det))/2a
      double sol2 = -(sqrt(det) + r.d.dot(r.e-c))/(r.d.dot(r.d));
      double closeSol = fmin(sol1,sol2);

      //if the solution occurs between the start and end times
      if (r.start<closeSol && closeSol<r.end ) {
        return closeSol;
      }
      else {
        return -1;
      }
    }
  }



};
