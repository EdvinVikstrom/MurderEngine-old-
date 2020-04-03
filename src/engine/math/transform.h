#ifndef TRANSFORM_H
  #define TRANSFORM_H

#include "vectors.h"

namespace me {

  struct transform {

    me::vec3d location, rotation, scale;

    transform(me::vec3d location, me::vec3d rotation, me::vec3d scale)
    {
      this->location = location;
      this->rotation = rotation;
      this->scale = scale;
    }

    transform() { }

  };

  struct transform2d {

    me::vec2d location, rotation, scale;

    transform2d(me::vec2d location, me::vec2d rotation, me::vec2d scale)
    {
      this->location = location;
      this->rotation = rotation;
      this->scale = scale;
    }

    transform2d() { }

  };

};

#endif
