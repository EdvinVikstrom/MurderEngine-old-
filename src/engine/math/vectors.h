#ifndef ME_VECTORS_H
  #define ME_VECTORS_H

#include "maths.h"

#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

namespace me {

  inline static real_t lengthSquared(me::vec3 &vec)
  {
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
  }

  inline static real_t length(me::vec3 &vec)
  {
    return me::maths::sqrt(lengthSquared(vec));
  }

  inline static me::vec3 normalize(me::vec3 &vec)
  {
    real_t len = real_t(1.0) / length(vec);
    return me::vec3(vec.x * len, vec.y * len, vec.z * len);
  }

};

#endif
