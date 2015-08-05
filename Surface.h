#include "ray.h"
#include "SimpleImage.h"

virtual class Surface {
public:
  RGBColor color;
  virtual RGBColor intersect(Ray r);
}
