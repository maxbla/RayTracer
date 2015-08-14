#include "SimpleImage.h"
#include "Eigen/Dense"
#include "AreaLight.h"

//forward declaration

class Surface {
public:
  RGBColor color;
  double shine;
  float ambientPercent;
  float diffusePercent;
  float specularPercent;
  Surface () {
    ;
  };
  virtual double intersect(Ray r) {return -1;}
  virtual Eigen::Vector4d calcNormal(Eigen::Vector4d position) {return (Eigen::Vector4d)NULL;}

  virtual RGBColor reflect(Ray viewingRay, double intersectionTime, AreaLight lights, std::vector<Surface*> surfaces, int reflectDepth) {
    Eigen::Vector4d normal = this->calcNormal(viewingRay.pointAt(intersectionTime));
    Eigen::Vector4d reflection = viewingRay.d + normal*((-viewingRay.d).dot(normal))*2;
    Ray reflectionRay = Ray(0.01,100.0, viewingRay.pointAt(intersectionTime),reflection);

    RGBColor reflectColor;
    //int maxReflectDepth = 1;
    double result;
    double depth;
    for(int i = 0; i<surfaces.size(); i+=1) {
      depth = -1.0;
      result = surfaces.at(i)->intersect(reflectionRay);
      if (result > 0.0 && (result < depth || depth < -.9)) {
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

  RGBColor shade (Ray viewingRay, double intersectionTime, AreaLight lights, std::vector<Surface*> surfaces) {

    Eigen::Vector4d normal = this->calcNormal(viewingRay.pointAt(intersectionTime));
    Eigen::Vector4d intersectionToLight = lights.location-(viewingRay.pointAt(intersectionTime));
    double distToLight = sqrt(intersectionToLight[0]*intersectionToLight[0]+
                              intersectionToLight[1]*intersectionToLight[1]+
                              intersectionToLight[2]*intersectionToLight[2]);
    intersectionToLight.normalize();
    double diffuseFactor = fmax(intersectionToLight.dot(normal),0);

    RGBColor c = this->color*ambientPercent;

    double shadow = 0.0;
    int numShadowRays = 128;
    bool inShadow;
    //soft shadow loop
    for(int k = 0; k<numShadowRays; k+=1 ) {
      Eigen::Vector4d intersectionToLight = lights.Sample(numShadowRays,k)-(viewingRay.pointAt(intersectionTime));
      Ray shadowRay(0.01,distToLight,viewingRay.pointAt(intersectionTime),intersectionToLight);
      inShadow = false;
      for (int i=0; i<surfaces.size() && !inShadow; i+=1) {
        if (surfaces.at(i)->intersect(shadowRay) > -.9 ) {
          inShadow = true;
        }
      }
      if (!inShadow) {
        shadow += 1.0;
      }
    }
    shadow = shadow/numShadowRays;
    c = c + (this->color)*diffusePercent*diffuseFactor*shadow;

    Eigen::Vector4d viewingDirection = -viewingRay.d;
    viewingDirection.normalize();

    Eigen::Vector4d reflection = -viewingDirection + normal*(viewingDirection.dot(normal))*2;
    reflection.normalize();
    double specularFloat = pow(fmax(0,reflection.dot(intersectionToLight)),20);

    c = c + (lights.color*specularPercent*specularFloat)*shadow;



    c.r = fmin(c.r,1.0);
    c.g = fmin(c.g,1.0);
    c.b = fmin(c.b,1.0);

    return c;
  }
};
