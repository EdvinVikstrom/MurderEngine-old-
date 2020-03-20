#ifndef VECTORS_H
  #define VECTORS_H

#include <cmath>
#include "maths.h"

/* very bad code */
/* try to find a better way;o maybe templates */

namespace me {

  /* [vectors] vec#t = { vec: "vector", #: dimension number, t: type((f)LOAT, (d)OUBLE, (i)NTEGER) } */
  struct vec2f { float x, y; vec2f() { } vec2f(float x, float y); };
  struct vec2d { double x, y; vec2d() { } vec2d(double x, double y); };
  struct vec2i { int x, y; vec2i() { } vec2i(int x, int y); };

  struct vec3f { float x, y, z; vec3f() { } vec3f(float x, float y, float z); };
  struct vec3d { double x, y, z; vec3d() { } vec3d(double x, double y, double z); };
  struct vec3i { int x, y, z; vec3i() { } vec3i(int x, int y, int z); };

  struct vec4f { float x, y, z, w; vec4f() { } vec4f(float x, float y, float z, float w); };
  struct vec4d { double x, y, z, w; vec4d() { } vec4d(double x, double y, double z, double w); };
  struct vec4i { int x, y, z, w; vec4i() { } vec4i(int x, int y, int z, int w); };

  /* utilities */
  void toVec2f(float* array, me::vec2f* dest, unsigned int count);
  void toVec2d(double* array, me::vec2d* dest, unsigned int count);
  void toVec2i(int* array, me::vec2i* dest, unsigned int count);

  void toVec3f(float* array, me::vec3f* dest, unsigned int count);
  void toVec3d(double* array, me::vec3d* dest, unsigned int count);
  void toVec3i(int* array, me::vec3i* dest, unsigned int count);

  void toVec4f(float* array, me::vec4f* dest, unsigned int count);
  void toVec4d(double* array, me::vec4d* dest, unsigned int count);
  void toVec4i(int* array, me::vec4i* dest, unsigned int count);

  void randomVec2f(float length, me::vec2f& vec);
  void randomVec2d(double length, me::vec2d& vec);
  void randomVec2i(int length, me::vec2i& vec);

  void randomVec3f(float length, me::vec3f& vec);
  void randomVec3d(double length, me::vec3d& vec);
  void randomVec3i(int length, me::vec3i& vec);

  void randomVec4f(float length, me::vec4f& vec);
  void randomVec4d(double length, me::vec4d& vec);
  void randomVec4i(int length, me::vec4i& vec);

};

#endif
