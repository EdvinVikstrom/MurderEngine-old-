#ifndef VECTORS_H
  #define VECTORS_H

namespace me {

  struct vec2f { float x, y; };
  struct vec2d { double x, y; };
  struct vec3f { float x, y, z; };
  struct vec3d { double x, y, z; };
  struct vec4f { float x, y, z, w; };
  struct vec4d { double x, y, z, w; };

  void toVec2f(float* array, me::vec2f* dest, unsigned int count);
  void toVec2d(double* array, me::vec2d* dest, unsigned int count);
  void toVec3f(float* array, me::vec3f* dest, unsigned int count);
  void toVec3d(double* array, me::vec3d* dest, unsigned int count);
  void toVec4f(float* array, me::vec4f* dest, unsigned int count);
  void toVec4d(double* array, me::vec4d* dest, unsigned int count);

};

#endif
