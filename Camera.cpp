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

/*takes the cross product of the first 3 components of a Vector4d, setting the 4th component of the result to 0.0*/
  Eigen::Vector4d Camera::cross4d(Eigen::Vector4d dir1, Eigen::Vector4d dir2) {
    Eigen::Vector3d temp = Eigen::Vector3d(dir1[0],dir1[1],dir1[2]).cross(Eigen::Vector3d(dir2[0],dir2[1],dir2[2]));
    return Eigen::Vector4d(temp[0],temp[1],temp[2],0.0);
  }

  Camera::Camera(double _maxDist, int _xRes, int _yRes, double _xHeight, double _yHeight,
    Eigen::Vector4d _eyepoint, Eigen::Vector4d _direction, Eigen::Vector4d _upDirection) {
      xRes = _xRes;
      yRes = _yRes;
      xHeight = _xHeight;
      yHeight = _yHeight;
      upDirection = _upDirection;
      upDirection.normalize();
      direction = _direction;
      positiveX = cross4d(upDirection,direction);
      positiveX.normalize();
      eyepoint = _eyepoint;
      maxDist = _maxDist;
    }

  Camera::Camera(double _maxDist, int _xRes, int _yRes, double _xHeight, double _yHeight,
    Eigen::Vector4d _eyepoint, Eigen::Vector4d _direction) {
      xRes = _xRes;
      yRes = _yRes;
      xHeight = _xHeight;
      yHeight = _yHeight;
      //default - positive z is the upwards direction
      upDirection = Eigen::Vector4d(0.0,1.0,0.0,0.0);
      direction = _direction;
      positiveX = cross4d(upDirection,direction);
      positiveX.normalize();
      eyepoint = _eyepoint;
      maxDist = _maxDist;
    }

  Camera::Camera(double _maxDist, int _xRes, int _yRes, double _xHeight, double _yHeight,
    Eigen::Vector4d _eyepoint) {
      xRes = _xRes;
      yRes = _yRes;
      xHeight = _xHeight;
      yHeight = _yHeight;
      upDirection = Eigen::Vector4d(0.0,1.0,0.0,0.0);
      //by default, look along the z axis
      direction = Eigen::Vector4d(0.0,0.0,1.0,0.0);
      positiveX = cross4d(upDirection,direction);
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
    upDirection = Eigen::Vector4d(0.0,1.0,0.0,0.0);
    positiveX = cross4d(upDirection,direction);
  }

  Ray Camera::ShootRay(int xPixel, int yPixel) {
    double xWorld = xPixel*(xHeight/xRes)-xHeight/2;
    double yWorld = yPixel*(-yHeight/yRes)+yHeight/2;
    Eigen::Vector4d rayDirection = xWorld*positiveX+yWorld*upDirection+direction;
    //std::cout<<xWorld<<' '<<yWorld<<std::endl;
    //std::cout<<direction.dot(Eigen::Vector4d(0,0,1.0,0))<<std::endl;
    return Ray(0,maxDist,eyepoint,rayDirection);
  }
