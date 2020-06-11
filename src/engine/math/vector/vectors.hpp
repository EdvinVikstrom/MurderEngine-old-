#ifndef ME_VECTORS_H
  #define ME_VECTORS_H

#include "maths.hpp"

#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"

namespace me {

  struct vec2i {
    int x, y;
    vec2i(int x, int y) { this->x = x; this->y = y; }
    vec2i() { x = 0; y = 0; }
  };
  struct vec3i {
    int x, y, z;
    vec3i(int x, int y, int z) { this->x = x; this->y = y; this->z = z; }
    vec3i() { x = 0; y = 0; z = 0; }
  };
  struct vec4i {
    int x, y, z, w;
    vec4i(int x, int y, int z, int w) { this->x = x; this->y = y; this->z = z; this->w = w; }
    vec4i() { x = 0; y = 0; z = 0; w = 0; }
  };

  struct vec2ui {
    uint32_t x, y;
    vec2ui(uint32_t x, uint32_t y) { this->x = x; this->y = y; }
    vec2ui() { x = 0; y = 0; }
  };
  struct vec3ui {
    int x, y, z;
    vec3ui(uint32_t x, uint32_t y, uint32_t z) { this->x = x; this->y = y; this->z = z; }
    vec3ui() { x = 0; y = 0; z = 0; }
  };
  struct vec4ui {
    int x, y, z, w;
    vec4ui(uint32_t x, uint32_t y, uint32_t z, uint32_t w) { this->x = x; this->y = y; this->z = z; this->w = w; }
    vec4ui() { x = 0; y = 0; z = 0; w = 0; }
  };

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
