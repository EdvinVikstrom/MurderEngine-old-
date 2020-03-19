#ifndef VECTORS_H
  #define VECTORS_H

namespace me {

  struct vec2f { float x, y; vec2f() { } vec2f(float x, float y); };
  struct vec2d { double x, y; vec2d() { } vec2d(double x, double y); };
  struct vec3f { float x, y, z; vec3f() { } vec3f(float x, float y, float z); };
  struct vec3d { double x, y, z; vec3d() { } vec3d(double x, double y, double z); };
  struct vec4f { float x, y, z, w; vec4f() { } vec4f(float x, float y, float z, float w); };
  struct vec4d { double x, y, z, w; vec4d() { } vec4d(double x, double y, double z, double w); };
  // How did it make a slope?

  void toVec2f(float* array, me::vec2f* dest, unsigned int count);
  void toVec2d(double* array, me::vec2d* dest, unsigned int count);
  void toVec3f(float* array, me::vec3f* dest, unsigned int count);
  void toVec3d(double* array, me::vec3d* dest, unsigned int count);
  void toVec4f(float* array, me::vec4f* dest, unsigned int count);
  void toVec4d(double* array, me::vec4d* dest, unsigned int count);

};

#endif
