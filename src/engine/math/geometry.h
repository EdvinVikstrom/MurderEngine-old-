#ifndef GEOMETRY_H
  #define GEOMETRY_H

#include "../kernel/array_utils.h"
#include "vectors.h"

namespace me {

  namespace gmt {

    struct shape {
      array<me::vec3f> points;
    };

    struct boundary {
      me::gmt::shape* shape;
    };

  };

};

#endif
