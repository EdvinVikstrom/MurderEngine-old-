#ifndef CAMERA_H
  #define CAMERA_H

namespace me {

  enum camera_type {
    PERSPECTIVE,
    ORTHOGRAPHIC
  };

  struct camera {
    std::string identifier;
    camera_type type;
    float focalLength;
    float aspectRatio;
    double znear, zfar;

    camera(std::string identifier, camera_type type, float focalLength, float aspectRatio, double znear, double zfar)
    {
      this->identifier = identifier;
      this->type = type;
      this->focalLength = focalLength;
      this->aspectRatio = aspectRatio;
      this->znear = znear;
      this->zfar = zfar;
    }

    camera() { }

  };

};

#endif
