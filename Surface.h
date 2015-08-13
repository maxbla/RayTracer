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
  
  RGBColor shade (Ray viewingRay, double intersectionTime, Light lights, std::vector<Surface*> surfaces) {
    float ambientPercent = 0.2;
    float diffusePercent = 0.5;
    float specularPercent = 0.3;

    Eigen::Vector4d normal = this->calcNormal(viewingRay.pointAt(intersectionTime));
    Eigen::Vector4d intersectionToLight = lights.location-(viewingRay.pointAt(intersectionTime));
    double distToLight = sqrt(intersectionToLight[0]*intersectionToLight[0]+
                              intersectionToLight[1]*intersectionToLight[1]+
                              intersectionToLight[2]*intersectionToLight[2]);
    intersectionToLight.normalize();
    double diffuseFactor = fmax(intersectionToLight.dot(normal),0);

    RGBColor c = this->color*ambientPercent;

    Ray shadowRay(0.01,distToLight,viewingRay.pointAt(intersectionTime),intersectionToLight);
    bool shadow = false;
    for (int i=0; i<surfaces.size(); i+=1) {
      if (surfaces.at(i)->intersect(shadowRay) > -.9 ) {
        shadow = true;
      }
    }
    if (!shadow) {
      c = c + (this->color)*diffusePercent*diffuseFactor;
    }

    Eigen::Vector4d viewingDirection = -viewingRay.pointAt(intersectionTime);
    viewingDirection.normalize();

    Eigen::Vector4d halfVector = (viewingDirection + intersectionToLight);
    halfVector.normalize();
    double specularFloat = pow(fmax(0,halfVector.dot(normal)),30);

    c = c + (lights.color*specularPercent*specularFloat);

    return c;
  }
};
