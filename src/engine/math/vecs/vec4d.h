#ifndef VEC_4D_H
  #define VEC_4D_H

me::vec4d::vec4d(double x, double y, double z, double w)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

me::vec4d* me::vec4d::add(me::vec4d &vec)
{
  this->x = this->x + vec.x;
  this->y = this->y + vec.y;
  this->z = this->z + vec.z;
  this->w = this->w + vec.w;
  return this;
}
me::vec4d* me::vec4d::sub(me::vec4d &vec)
{
  this->x = this->x - vec.x;
  this->y = this->y - vec.y;
  this->z = this->z - vec.z;
  this->w = this->w - vec.w;
  return this;
}
me::vec4d* me::vec4d::mul(me::vec4d &vec)
{
  this->x = this->x * vec.x;
  this->y = this->y * vec.y;
  this->z = this->z * vec.z;
  this->w = this->w * vec.w;
  return this;
}
me::vec4d* me::vec4d::div(me::vec4d &vec)
{
  this->x = this->x / vec.x;
  this->y = this->y / vec.y;
  this->z = this->z / vec.z;
  this->w = this->w / vec.w;
  return this;
}

me::vec4d* me::vec4d::add(double fac)
{
  this->x = this->x + fac;
  this->y = this->y + fac;
  this->z = this->z + fac;
  this->w = this->w + fac;
  return this;
}
me::vec4d* me::vec4d::sub(double fac)
{
  this->x = this->x - fac;
  this->y = this->y - fac;
  this->z = this->z - fac;
  this->w = this->w - fac;
  return this;
}
me::vec4d* me::vec4d::mul(double fac)
{
  this->x = this->x * fac;
  this->y = this->y * fac;
  this->z = this->z * fac;
  this->w = this->w * fac;
  return this;
}
me::vec4d* me::vec4d::div(double fac)
{
  this->x = this->x / fac;
  this->y = this->y / fac;
  this->z = this->z / fac;
  this->w = this->w / fac;
  return this;
}

#endif
