#include "SimpleImage.h"

//forward declaration

class Surface {
public:
  RGBColor color;
  Surface () {
    ;
  };
  virtual double intersect(Ray r) {return -1;}
};
