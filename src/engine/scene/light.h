#ifndef LIGHT_H
  #define LIGHT_H

#include "../math/vectors.h"
#include "scene.h"

namespace me {

  struct light : public item {
    double power;
    double size;
    me::vec4f* rgba;
  };

};

#endif
