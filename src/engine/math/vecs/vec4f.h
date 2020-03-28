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
  this->x = this->x + vec.x;
  this->y = this->y + vec.y;
  this->z = this->z + vec.z;
  this->w = this->w + vec.w;
}
void me::vec4f::sub(me::vec4f &vec)
{
  this->x = this->x - vec.x;
  this->y = this->y - vec.y;
  this->z = this->z - vec.z;
  this->w = this->w - vec.w;
}
void me::vec4f::mul(me::vec4f &vec)
{
  this->x = this->x * vec.x;
  this->y = this->y * vec.y;
  this->z = this->z * vec.z;
  this->w = this->w * vec.w;
}
void me::vec4f::div(me::vec4f &vec)
{
  this->x = this->x / vec.x;
  this->y = this->y / vec.y;
  this->z = this->z / vec.z;
  this->w = this->w / vec.w;
}

void me::vec4f::add(float fac)
{
  this->x = this->x + fac;
  this->y = this->y + fac;
  this->z = this->z + fac;
  this->w = this->w + fac;
}
void me::vec4f::sub(float fac)
{
  this->x = this->x - fac;
  this->y = this->y - fac;
  this->z = this->z - fac;
  this->w = this->w - fac;
}
void me::vec4f::mul(float fac)
{
  this->x = this->x * fac;
  this->y = this->y * fac;
  this->z = this->z * fac;
  this->w = this->w * fac;
}
void me::vec4f::div(float fac)
{
  this->x = this->x / fac;
  this->y = this->y / fac;
  this->z = this->z / fac;
  this->w = this->w / fac;
}

#endif
