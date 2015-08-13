class Light {
public:
  Eigen::Vector4d location;
  RGBColor color;

  Light() {
    location = Eigen::Vector4d(0.0,0.0,0.0,1.0);
    color = RGBColor(1.0,1.0,1.0);
  }

  Light(Eigen::Vector4d location, RGBColor color) {
    this->location = location;
    this->color = color;
  }
};
