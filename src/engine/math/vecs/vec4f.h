#ifndef VEC_4F_H
  #define VEC_4F_H

me::vec4f::vec4f(float x, float y, float z, float w)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

void me::vec4f::add(me::vec4f &vec)
{
  this->x+=vec.x;
  this->y+=vec.y;
  this->z+=vec.z;
  this->w+=vec.w;
}
void me::vec4f::sub(me::vec4f &vec)
{
}
void me::vec4f::mul(me::vec4f &vec)
{
}
void me::vec4f::div(me::vec4f &vec)
{
}

#endif
