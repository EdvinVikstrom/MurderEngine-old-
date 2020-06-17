#ifndef TRANSFORM_HPP
  #define TRANSFORM_HPP

namespace me {

  struct transform {

    struct {
      double x, y, z;
    } location, rotation, scale;

    transform(double locX, double locY, double locZ,
              double rotX, double rotY, double rotZ,
              double scaleX, double scaleY, double scaleZ)
    {
      location = {locX, locY, locZ};
      rotation = {rotX, rotY, rotZ};
      scale = {scaleX, scaleY, scaleZ};
    }

    transform()
    {
      location = {0.0D, 0.0D, 0.0D};
      rotation = {0.0D, 0.0D, 0.0D};
      scale = {0.0D, 0.0D, 0.0D};
    }

  };

};

#endif
