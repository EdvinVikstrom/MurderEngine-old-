#ifndef CAMERA_H
  #define CAMERA_H

#define ME_CAMERA_PERSPECTIVE              0x45
#define ME_CAMERA_ORTHO                    0x47

#include "../math/vectors.h"
#include "scene.h"
#include <string>

namespace me {

  struct camera : public item {
    unsigned int type; // TODO: Find the right name
    float aspectRatio;
    /* FOV (Field Of View) */
    float focalLength;
    double znear, zfar;

    camera(std::string identifier, me::vec3d position, me::vec3d rotation, me::vec3d scale, unsigned int type, float aspectRatio, float focalLength, double znear, double zfar)
    {
      this->identifier = identifier;
      this->position = position;
      this->rotation = rotation;
      this->scale = scale;
      this->type = type;
      this->aspectRatio = aspectRatio;
      this->focalLength = focalLength;
      this->znear = znear;
      this->zfar = zfar;
    }

  };

};

#endif
