#include "SimpleImage.h"

//forward declaration
class Ray;

class Surface {
public:
  RGBColor color;
  virtual double intersect(Ray r);
};
