#include <cmath>
#include "maths.h"
#include "vectors.h"

#include "vecs/vec2f.h"
#include "vecs/vec2d.h"
#include "vecs/vec2i.h"
#include "vecs/vec3f.h"
#include "vecs/vec3d.h"
#include "vecs/vec3i.h"
#include "vecs/vec4f.h"
#include "vecs/vec4d.h"
#include "vecs/vec4i.h"

void me::toVec2f(float* array, me::vec2f* dest, unsigned int count)
{
  for (unsigned int i = 0; i < count; i+=2)
  {
    dest[i/2].x = array[i];
    dest[i/2].y = array[i+1];
  }
}
void me::toVec2d(double* array, me::vec2d* dest, unsigned int count)
{
  for (unsigned int i = 0; i < count; i+=2)
  {
    dest[i/2].x = array[i];
    dest[i/2].y = array[i+1];
  }
}
void me::toVec2i(int* array, me::vec2i* dest, unsigned int count)
{
  for (unsigned int i = 0; i < count; i+=2)
  {
    dest[i/2].x = array[i];
    dest[i/2].y = array[i+1];
  }
}

void me::toVec3f(float* array, me::vec3f* dest, unsigned int count)
{
  for (unsigned int i = 0; i < count; i+=3)
  {
    dest[i/3].x = array[i];
    dest[i/3].y = array[i+1];
    dest[i/3].z = array[i+2];
  }
}
void me::toVec3d(double* array, me::vec3d* dest, unsigned int count)
{
  for (unsigned int i = 0; i < count; i+=3)
  {
    dest[i/3].x = array[i];
    dest[i/3].y = array[i+1];
    dest[i/3].z = array[i+2];
  }
}
void me::toVec3i(int* array, me::vec3i* dest, unsigned int count)
{
  for (unsigned int i = 0; i < count; i+=3)
  {
    dest[i/3].x = array[i];
    dest[i/3].y = array[i+1];
    dest[i/3].z = array[i+2];
  }
}

void me::toVec4f(float* array, me::vec4f* dest, unsigned int count)
{
  for (unsigned int i = 0; i < count; i+=4)
  {
    dest[i/4].x = array[i];
    dest[i/4].y = array[i+1];
    dest[i/4].z = array[i+2];
    dest[i/4].w = array[i+3];
  }
}
void me::toVec4d(double* array, me::vec4d* dest, unsigned int count)
{
  for (unsigned int i = 0; i < count; i+=4)
  {
    dest[i/4].x = array[i];
    dest[i/4].y = array[i+1];
    dest[i/4].z = array[i+2];
    dest[i/4].w = array[i+3];
  }
}
void me::toVec4i(int* array, me::vec4i* dest, unsigned int count)
{
  for (unsigned int i = 0; i < count; i+=4)
  {
    dest[i/4].x = array[i];
    dest[i/4].y = array[i+1];
    dest[i/4].z = array[i+2];
    dest[i/4].w = array[i+3];
  }
}


void me::randomVec2f(float length, me::vec2f &vec)
{
  vec.x = (float) sin(maths::rand() * TAU)*length;
  vec.y = (float) cos(maths::rand() * TAU)*length;
}
void me::randomVec2d(double length, me::vec2d &vec)
{
  vec.x = (double) sin(maths::rand() * TAU)*length;
  vec.y = (double) cos(maths::rand() * TAU)*length;
}
void me::randomVec2i(int length, me::vec2i &vec)
{
  vec.x = (int) sin(maths::rand() * TAU)*length;
  vec.y = (int) cos(maths::rand() * TAU)*length;
}

void me::randomVec3f(float length, me::vec3f &vec)
{
  vec.x = (float) sin(maths::rand() * TAU)*length;
  vec.y = (float) cos(maths::rand() * TAU)*length;
  vec.z = (float) cos(maths::rand() * TAU)*length;
}
void me::randomVec3d(double length, me::vec3d &vec)
{
  vec.x = (double) sin(maths::rand() * TAU)*length;
  vec.y = (double) cos(maths::rand() * TAU)*length;
  vec.z = (double) cos(maths::rand() * TAU)*length;
}
void me::randomVec3i(int length, me::vec3i &vec)
{
  vec.x = (int) sin(maths::rand() * TAU)*length;
  vec.y = (int) cos(maths::rand() * TAU)*length;
  vec.z = (int) cos(maths::rand() * TAU)*length;
}

void me::randomVec4f(float length, me::vec4f &vec)
{
  vec.x = (float) sin(maths::rand() * TAU)*length;
  vec.y = (float) cos(maths::rand() * TAU)*length;
  vec.z = (float) cos(maths::rand() * TAU)*length;
  vec.w = (float) sin(maths::rand() * TAU)*length;
}
void me::randomVec4d(double length, me::vec4d &vec)
{
  vec.x = (double) sin(maths::rand() * TAU)*length;
  vec.y = (double) cos(maths::rand() * TAU)*length;
  vec.z = (double) cos(maths::rand() * TAU)*length;
  vec.w = (double) sin(maths::rand() * TAU)*length;
}
void me::randomVec4i(int length, me::vec4i &vec)
{
  vec.x = (int) sin(maths::rand() * TAU)*length;
  vec.y = (int) cos(maths::rand() * TAU)*length;
  vec.z = (int) cos(maths::rand() * TAU)*length;
  vec.w = (int) sin(maths::rand() * TAU)*length;
}
