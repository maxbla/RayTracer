#include "SimpleImage.h"
#include "Eigen/Dense"
#include "Light.h"

//forward declaration

class Surface {
public:
  RGBColor color;
  double shine;
  Surface () {
    ;
  };
  virtual double intersect(Ray r) {return -1;}
  virtual Eigen::Vector4d calcNormal(Eigen::Vector4d position) {return (Eigen::Vector4d)NULL;}

  RGBColor reflect(Ray viewingRay, double intersectionTime, Light lights, std::vector<Surface*> surfaces, int reflectDepth) {
    Eigen::Vector4d normal = this->calcNormal(viewingRay.pointAt(intersectionTime));
    Eigen::Vector4d reflection = viewingRay.d + normal*((-viewingRay.d).dot(normal))*2;
    Ray reflectionRay = Ray(0.1,100.0, viewingRay.pointAt(intersectionTime),reflection);

    RGBColor reflectColor;
    int maxReflectDepth = 1;
    double result;
    for(int i = 0; i<surfaces.size(); i+=1) {
      double depth = -1.0;
      result = surfaces.at(i)->intersect(reflectionRay);
      if (result>=0.0 && (result < depth || depth < -.9)) {
        reflectColor = surfaces.at(i)->shade(reflectionRay,result,lights,surfaces);
      }
    }
    /*
    if (reflectDepth <= maxReflectDepth) {
      RGBColor nextReflectionColor = reflect(viewingRay, intersectionTime,lights,surfaces,reflectDepth+1);
      return (reflectColor*(fmax((float)(reflectDepth-1),1.0)/reflectDepth) + nextReflectionColor*(1.0/((float)reflectDepth)));
    }
    */
    /*
    else {*/
      return reflectColor;
    //}
  }

  RGBColor shade (Ray viewingRay, double intersectionTime, Light lights, std::vector<Surface*> surfaces) {
    float ambientPercent = 0.2;
    float diffusePercent = 0.7;
    float specularPercent = 0.5;

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

    Eigen::Vector4d viewingDirection = -viewingRay.d;
    viewingDirection.normalize();

    Eigen::Vector4d reflection = -viewingDirection + normal*(viewingDirection.dot(normal))*2;
    reflection.normalize();
    double specularFloat = pow(fmax(0,reflection.dot(intersectionToLight)),20);

    if(!shadow) {
      c = c + (lights.color*specularPercent*specularFloat);
    }



    c.r = fmin(c.r,1.0);
    c.g = fmin(c.g,1.0);
    c.b = fmin(c.b,1.0);

    return c;
  }
};
