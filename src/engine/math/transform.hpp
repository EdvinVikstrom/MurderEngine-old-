#ifndef TRANSFORM_HPP
  #define TRANSFORM_HPP

#include "maths.hpp"

namespace me {

  struct transform {

    me::vec3 location, rotation, scale;

    transform(me::vec3 location, me::vec3 rotation, me::vec3 scale)
    {
      this->location = location;
      this->rotation = rotation;
      this->scale = scale;
    }

    transform() { }

  };

};

#endif
