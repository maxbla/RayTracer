#include "Camera.h"
//#include "Ray.h"
/*
    double maxDist;
    int xRes;
    int yRes;
    double xHeight;
    double yHeight;
    double direction;
    Vector4d eyepoint;
*/
    Camera::Camera(double _maxDist, int _xRes, int _yRes, double _xHeight, double _yHeight,
      Eigen::Vector4d _direction, Eigen::Vector4d _eyepoint) {
        xRes = _xRes;
        yRes = _yRes;
        xHeight = _xHeight;
        yHeight = _yHeight;
        //default - up is the upwards direction
        upDirection = Eigen::Vector4d(0.0,1.0,0.0,0.0);
        direction = _direction;
        eyepoint = _eyepoint;
        maxDist = _maxDist;
      }

      Camera::Camera(double _maxDist, int _xRes, int _yRes, double _xHeight, double _yHeight,
        Eigen::Vector4d _eyepoint) {
          xRes = _xRes;
          yRes = _yRes;
          xHeight = _xHeight;
          yHeight = _yHeight;
          //by default, look along the z axis
          direction = Eigen::Vector4d(0.0,0.0,1.0,0.0);
          eyepoint = _eyepoint;
          maxDist = _maxDist;
        }

    Camera::Camera(){
      maxDist = 0.0;
      xRes = 0;
      yRes = 0;
      xHeight = 0.0;
      yHeight = 0.0;
      direction = Eigen::Vector4d(0.0,0.0,1.0,0.0);
      eyepoint = Eigen::Vector4d(0.0,0.0,0.0,-1.0);
    }

    Ray Camera::ShootRay(int xPixel, int yPixel) {
      double xWorld = xPixel*(xHeight/xRes)-xHeight/2;
      double yWorld = yPixel*(-yHeight/yRes)+yHeight/2;
      //std::cout<<xWorld<<' '<<yWorld<<std::endl;
      //std::cout<<(eyepoint+direction+Eigen::Vector4d(xWorld,yWorld,0.0,0.0)).dot(Eigen::Vector4d(1.0,0.0,0.0,0.0))<<' '<<(eyepoint+direction+Eigen::Vector4d(xWorld,yWorld,0.0,0.0)).dot(Eigen::Vector4d(0.0,1.0,0.0,0.0))<<' '<<(eyepoint+direction+Eigen::Vector4d(xWorld,yWorld,0.0,0.0)).dot(Eigen::Vector4d(0.0,0.0,1.0,0.0))<<std::endl;
      //std::cout<<direction.dot(Eigen::Vector4d(0,0,1.0,0))<<std::endl;
      return Ray(0,100,eyepoint,direction+Eigen::Vector4d(xWorld,yWorld,0.0,0.0));
    }
