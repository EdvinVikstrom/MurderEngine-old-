#ifndef GEOMETRY_H
  #define GEOMETRY_H

#include "../utilities/ArrayUtils.h"
#include "vectors.h"

namespace me {

  namespace gmt {

    struct shape {
      me::array<me::vec3f> points;
    };

    struct boundary {
      me::gmt::shape* shape;
    };

  };

};

#endif
