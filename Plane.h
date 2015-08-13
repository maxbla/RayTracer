class Plane: public Surface {
public:
  //a single point known to be on the plane
  Eigen::Vector4d pt;
  //the normal vector to the surface of the plane
  Eigen::Vector4d norm;

  //default constructor
  Plane () {
    pt = Eigen::Vector4d (0.0,0.0,0.0,1.0);
    norm = Eigen::Vector4d (0.0,0.0,1.0,0.0);
    color = RGBColor(0.9,0.9,0.9);
  }

  Plane (Eigen::Vector4d point,Eigen::Vector4d normal) {
    pt = point;
    norm = normal;
    color = RGBColor(0.9,0.9,0.9);
  }

  Plane (Eigen::Vector4d point,Eigen::Vector4d normal, RGBColor c) {
    pt = point;
    norm = normal;
    color = c;
  }

  double intersect (Ray r) {
    double det = norm.dot(r.d);
    //std::cout<<det<<std::endl;
    if (det == 0.0) {
      //std::cout<<"det == 0"<<std::endl;
      return -1.0;
    }
    else {
      double t = norm.dot(pt-r.e)/det;
      if (r.isInRange(t)) {
        //std::cout<<"t is in range with value "<<t<<std::endl;
        return t;
      }
      else {
        //std::cout<<"t is out of range"<<std::endl;
        return -1;
      }
    }
  }

  Eigen::Vector4d calcNormal (Eigen::Vector4d position) {
    return norm;
  }

  RGBColor shade(Ray viewingRay, double intersectionTime, Light light, std::vector<Surface*> surfaces) {
    float ambientPercent = .2;
    float diffusePercent = .8;

    Eigen::Vector4d normal = this->norm;
    Eigen::Vector4d intersectionToLight = light.location-(viewingRay.pointAt(intersectionTime));
    double distToLight = sqrt(intersectionToLight[0]*intersectionToLight[0]+
                              intersectionToLight[1]*intersectionToLight[1]+
                              intersectionToLight[2]*intersectionToLight[2]);
    intersectionToLight.normalize();
    double factor = fmax(intersectionToLight.dot(normal),0);
    //std::cout<<factor<<std::endl;

    RGBColor c = this->color*ambientPercent;

    Ray shadowRay(0.01,distToLight,viewingRay.pointAt(intersectionTime),intersectionToLight);
    bool shadow = false;
    for (int i=0; i<surfaces.size(); i+=1) {
      if (surfaces.at(i)->intersect(shadowRay) > -.9 ) {
        shadow = true;
      }
    }
    if (!shadow) {
      c = c + (this->color)*diffusePercent*factor;
    }

    return c;
  }
};
