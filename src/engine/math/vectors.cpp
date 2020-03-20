#include "vectors.h"

me::vec2f::vec2f(float x, float y)
{
  vec2f::x = x;
  vec2f::y = y;
}
me::vec2d::vec2d(double x, double y)
{
  vec2d::x = x;
  vec2d::y = y;
}
me::vec2i::vec2i(int x, int y)
{
  vec2i::x = x;
  vec2i::y = y;
}

me::vec3f::vec3f(float x, float y, float z)
{
  vec3f::x = x;
  vec3f::y = y;
  vec3f::z = z;
}
me::vec3d::vec3d(double x, double y, double z)
{
  vec3d::x = x;
  vec3d::y = y;
  vec3d::z = z;
}
me::vec3i::vec3i(int x, int y, int z)
{
  vec3i::x = x;
  vec3i::y = y;
  vec3i::z = z;
}

me::vec4f::vec4f(float x, float y, float z, float w)
{
  vec4f::x = x;
  vec4f::y = y;
  vec4f::z = z;
  vec4f::w = w;
}
me::vec4d::vec4d(double x, double y, double z, double w)
{
  vec4d::x = x;
  vec4d::y = y;
  vec4d::z = z;
  vec4d::w = w;
}
me::vec4i::vec4i(int x, int y, int z, int w)
{
  vec4i::x = x;
  vec4i::y = y;
  vec4i::z = z;
  vec4i::w = w;
}

/* Functions */

/* Helpers */

void me::toVec2f(float* array, me::vec2f* dest, unsigned int count)
{
  for (int i = 0; i < count; i+=2)
  {
    dest[i/2].x = array[i];
    dest[i/2].y = array[i+1];
  }
}
void me::toVec2d(double* array, me::vec2d* dest, unsigned int count)
{
  for (int i = 0; i < count; i+=2)
  {
    dest[i/2].x = array[i];
    dest[i/2].y = array[i+1];
  }
}
void me::toVec2i(int* array, me::vec2i* dest, unsigned int count)
{
  for (int i = 0; i < count; i+=2)
  {
    dest[i/2].x = array[i];
    dest[i/2].y = array[i+1];
  }
}

void me::toVec3f(float* array, me::vec3f* dest, unsigned int count)
{
  for (int i = 0; i < count; i+=3)
  {
    dest[i/3].x = array[i];
    dest[i/3].y = array[i+1];
    dest[i/3].z = array[i+2];
  }
}
void me::toVec3d(double* array, me::vec3d* dest, unsigned int count)
{
  for (int i = 0; i < count; i+=3)
  {
    dest[i/3].x = array[i];
    dest[i/3].y = array[i+1];
    dest[i/3].z = array[i+2];
  }
}
void me::toVec3i(int* array, me::vec3i* dest, unsigned int count)
{
  for (int i = 0; i < count; i+=3)
  {
    dest[i/3].x = array[i];
    dest[i/3].y = array[i+1];
    dest[i/3].z = array[i+2];
  }
}

void me::toVec4f(float* array, me::vec4f* dest, unsigned int count)
{
  for (int i = 0; i < count; i+=4)
  {
    dest[i/4].x = array[i];
    dest[i/4].y = array[i+1];
    dest[i/4].z = array[i+2];
    dest[i/4].w = array[i+3];
  }
}
void me::toVec4d(double* array, me::vec4d* dest, unsigned int count)
{
  for (int i = 0; i < count; i+=4)
  {
    dest[i/4].x = array[i];
    dest[i/4].y = array[i+1];
    dest[i/4].z = array[i+2];
    dest[i/4].w = array[i+3];
  }
}
void me::toVec4i(int* array, me::vec4i* dest, unsigned int count)
{
  for (int i = 0; i < count; i+=4)
  {
    dest[i/4].x = array[i];
    dest[i/4].y = array[i+1];
    dest[i/4].z = array[i+2];
    dest[i/4].w = array[i+3];
  }
}

void randomVec2f(float length, me::vec2f& vec)
{
  vec.x = (float) sin(maths::rand()*PI2)*length;
  vec.y = (float) cos(maths::rand()*PI2)*length;
}
void randomVec2d(double length, me::vec2d& vec)
{
  vec.x = sin(maths::rand()*PI2)*length;
  vec.y = cos(maths::rand()*PI2)*length;
}
void randomVec2i(int length, me::vec2i& vec)
{
  vec.x = (int) sin(maths::rand()*PI2)*length;
  vec.y = (int) cos(maths::rand()*PI2)*length;
}

void randomVec3f(float length, me::vec3f& vec)
{
  vec.x = (float) sin(maths::rand()*PI2)*length;
  vec.y = (float) cos(maths::rand()*PI2)*length;
  vec.z = (float) cos(maths::rand()*PI2)*length;
}
void randomVec3d(double length, me::vec3d& vec)
{
  vec.x = sin(maths::rand()*PI2)*length;
  vec.y = cos(maths::rand()*PI2)*length;
  vec.z = cos(maths::rand()*PI2)*length;
}
void randomVec3i(int length, me::vec3i& vec)
{
  vec.x = (int) sin(maths::rand()*PI2)*length;
  vec.y = (int) cos(maths::rand()*PI2)*length;
  vec.z = (int) cos(maths::rand()*PI2)*length;
}

void randomVec4f(float length, me::vec4f& vec)
{
  vec.x = (float) sin(maths::rand()*PI2)*length;
  vec.y = (float) cos(maths::rand()*PI2)*length;
  vec.z = (float) cos(maths::rand()*PI2)*length;
  vec.w = (float) sin(maths::rand()*PI2)*length;
}
void randomVec4d(double length, me::vec4d& vec)
{
  vec.x = sin(maths::rand()*PI2)*length;
  vec.y = cos(maths::rand()*PI2)*length;
  vec.z = cos(maths::rand()*PI2)*length;
  vec.w = sin(maths::rand()*PI2)*length;
}
void randomVec4i(int length, me::vec4i& vec)
{
  vec.x = (int) sin(maths::rand()*PI2)*length;
  vec.y = (int) cos(maths::rand()*PI2)*length;
  vec.z = (int) cos(maths::rand()*PI2)*length;
  vec.w = (int) sin(maths::rand()*PI2)*length;
}
