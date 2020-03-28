#ifndef VEC_3F_H
  #define VEC_3F_H

me::vec3f::vec3f(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

void me::vec3f::add(me::vec3f &vec)
{
  this->x+=vec.x;
  this->y+=vec.y;
  this->z+=vec.z;
}
void me::vec3f::sub(me::vec3f &vec)
{
}
void me::vec3f::mul(me::vec3f &vec)
{
}
void me::vec3f::div(me::vec3f &vec)
{
}

#endif
