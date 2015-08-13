#include "Surface.h"
//#include "Ray.h"
#include <math.h>

class Sphere: public Surface {
public:
  //center of sphere
  Eigen::Vector4d c;
  //radius of sphere
  double rad;

  Sphere () {
    c = Eigen::Vector4d(0.0,0.0,0.0,0.0);
    rad = 1.0;
    color = RGBColor(1.0,1.0,1.0);
  }

  Sphere(Eigen::Vector4d center, double radius){
    c = center;
    rad = radius;
    color = RGBColor(1.0,1.0,1.0);
  }

  Sphere(Eigen::Vector4d center, double radius, RGBColor color) {
    c = center;
    rad = radius;
    this->color = color;
  }

  /*returns the time value at the intersection of the ray and sphere*/
  double intersect(Ray r) {
    //calculate determinant of intersection equation
    /*std::cout<<(r.d).dot(Eigen::Vector4d(1.0,0.0,0.0,0.0))<<' '
    <<(r.d).dot(Eigen::Vector4d(0.0,1.0,0.0,0.0))<<' '<<(r.d).dot(Eigen::Vector4d(0.0,0.0,1.0,0.0))<<std::endl;*/
    double det = (r.d.dot(r.e-c))*(r.d.dot(r.e-c)) - (r.d.dot(r.d))*((r.e-c).dot(r.e-c)-rad*rad);
    //std::cout<<det<<std::endl;2
    if (det < 0) {
      return -1;
    }
    else { //problem has 2 solutions
      //solution 1 where t = (-b + sqrt(desc))/2a
      double sol1 = (sqrt(det) - r.d.dot(r.e-c))/(r.d.dot(r.d));
      //solution 2 where t = -(b + sqrt(desc))/2a
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

  //assuming the given position is on the sphere, finds the normal of the spherea at that point
  Eigen::Vector4d calcNormal (Eigen::Vector4d position) {
    Eigen::Vector4d value = position - c;
    value.normalize();
    return value;
  }

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
