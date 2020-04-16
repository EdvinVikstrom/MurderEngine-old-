#ifndef ME_VECTORS_H
  #define ME_VECTORS_H

#include "maths.h"

#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

namespace me {

  inline static real_t lengthSquared(me::vec3 vec)
  {
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
  }

  inline static real_t length(me::vec3 vec)
  {
    return me::maths::sqrt(lengthSquared(vec));
  }

  inline static me::vec3 normalize(me::vec3 vec)
  {
    real_t len = real_t(1.0) / length(vec);
    return me::vec3(vec.x * len, vec.y * len, vec.z * len);
  }

  inline static float dot(me::vec3 vec1, me::vec3 vec2)
  {
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
  }

  inline static me::vec3 cross(me::vec3 vec1, me::vec3 vec2)
  {
    float rx = vec1.y * vec2.z - vec1.z * vec2.y;
    float ry = vec1.z * vec2.x - vec1.x * vec2.z;
    float rz = vec1.x * vec2.y - vec1.y * vec2.x;
    return me::vec3(rx, ry, rz);
  }

};

#endif
