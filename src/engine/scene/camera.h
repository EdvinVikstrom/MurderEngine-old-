#ifndef CAMERA_H
  #define CAMERA_H

namespace me {

  enum camera_type {
    PERSPECTIVE,
    ORTHOGRAPHIC,
    VIEW_2D,
    ENC_VIEW_2D
  };

  struct camera {
    std::string identifier;
    camera_type type;
    float focalLength;
    float aspectRatio;
    double znear, zfar;
    unsigned int width, height;
    me::transform transform;

    camera(std::string identifier, camera_type type, float focalLength, float aspectRatio, double znear, double zfar, unsigned int width, unsigned int height, me::transform &transform)
    {
      this->identifier = identifier;
      this->type = type;
      this->focalLength = focalLength;
      this->aspectRatio = aspectRatio;
      this->znear = znear;
      this->zfar = zfar;
      this->width = width;
      this->height = height;
      this->transform = transform;
    }

    camera() { }

  };

};

#endif
