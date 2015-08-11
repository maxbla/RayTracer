#include "Surface.h"

class Plane: public Surface {

  //a single point known to be on the plane
  Eigen::Vector4d pt;
  //the normal vector to the surface of the plane
  Eigen::Vector4d norm;
  //the color of the plane
  RGBColor color;

  //default constructor
  Plane () {
    pt = Eigen::Vector4d (0.0,0.0,0.0,1.0);
    norm = Eigen::Vector4d (0.0,0.0,1.0,0.0);
    color = RGBColor(0.9,0.9,0.9);
  }

  Plane (Eigen::Vector4d point,Eigen::Vector4d normal) {
    pt = point;
    norm = normal;
    color = RGBColor(0.9,0.9,0.9);
  }

  Plane (Eigen::Vector4d point,Eigen::Vector4d normal, RGBColor c) {
    pt = point;
    norm = normal;
    color = c;
  }

  double intersect (Ray r) {
    det = norm.dot(r.d);
    if (det == 0.0) {
      return -1.0;
    }
    else {
      double t = norm.dot(pt-r.e)/det;
      if (r.isInRange(t)) {
        return t;
      }
      else {
        return -1;
      }
    }
  }

  Eigen::Vector4d calcNormal (Eigen::Vector4d position) {
    return norm;
  }
}
