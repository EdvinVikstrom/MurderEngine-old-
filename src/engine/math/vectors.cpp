#include "vectors.h"

/* Constructors */
me::vec2d::vec2d(double x, double y)
{
  vec2d::x = x;
  vec2d::y = y;
}

me::vec2d::vec2f(float x, float y)
{
  vec2f::x = x;
  vec2f::y = y;
}

me::vec2d::vec3d(double x, double y, double z)
{
  vec3d::x = x;
  vec3d::y = y;
  vec3d::z = z;
}

me::vec2d::vec3f(float x, float y, float z)
{
  vec3f::x = x;
  vec3f::y = y;
  vec3f::z = z;
}

me::vec2d::vec4d(double x, double y, double z, double w)
{
  vec4d::x = x;
  vec4d::y = y;
  vec4d::z = z;
  vec4d::w = w;
}

me::vec2d::vec4f(float x, float y, float z, float w)
{
  vec4f::x = x;
  vec4f::y = y;
  vec4f::z = z;
  vec4f::w = w;
}

/* Functions */

/* Helpers */

void toVec2f(float* array, me::vec2f* dest, unsigned int count)
{
  for (int i = 0; i < count; i+=2)
  {
    dest[i/2].x = array[i];
    dest[i/2].y = array[i+1];
  }
}
void toVec2d(double* array, me::vec2d* dest, unsigned int count)
{
  for (int i = 0; i < count; i+=2)
  {
    dest[i/2].x = array[i];
    dest[i/2].y = array[i+1];
  }
}
void toVec3f(float* array, me::vec3f* dest, unsigned int count)
{
  for (int i = 0; i < count; i+=3)
  {
    dest[i/3].x = array[i];
    dest[i/3].y = array[i+1];
    dest[i/3].z = array[i+2];
  }
}
void toVec3d(double* array, me::vec3d* dest, unsigned int count)
{
  for (int i = 0; i < count; i+=3)
  {
    dest[i/3].x = array[i];
    dest[i/3].y = array[i+1];
    dest[i/3].z = array[i+2];
  }
}
void toVec4f(float* array, me::vec4f* dest, unsigned int count)
{
  for (int i = 0; i < count; i+=4)
  {
    dest[i/4].x = array[i];
    dest[i/4].y = array[i+1];
    dest[i/4].z = array[i+2];
    dest[i/4].w = array[i+3];
  }
}
void toVec4d(double* array, me::vec4d* dest, unsigned int count)
{
  for (int i = 0; i < count; i+=4)
  {
    dest[i/4].x = array[i];
    dest[i/4].y = array[i+1];
    dest[i/4].z = array[i+2];
    dest[i/4].w = array[i+3];
  }
}
