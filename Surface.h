#include "SimpleImage.h"
#include "Eigen/Dense"
#include "Light.h"

//forward declaration

class Surface {
public:
  RGBColor color;
  Surface () {
    ;
  };
  virtual double intersect(Ray r) {return -1;}
  virtual Eigen::Vector4d calcNormal(Eigen::Vector4d position) {return (Eigen::Vector4d)NULL;}
  virtual RGBColor shade(Ray viewingRay, double intersectionTime, Light lights, std::vector<Surface*> surfaces) {return RGBColor();}
};
