#include "SimpleImage.h"
#include "Eigen/Dense"

//forward declaration

class Surface {
public:
  RGBColor color;
  Surface () {
    ;
  };
  virtual double intersect(Ray r) {return -1;}
  virtual Eigen::Vector4d calcNormal(Eigen::Vector4d position) {return (Eigen::Vector4d)NULL;}
};
