#ifndef VEC_3D_H
  #define VEC_3D_H

me::vec3d::vec3d(double x, double y, double z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

me::vec3d* me::vec3d::add(me::vec3d &vec)
{
  this->x = this->x + vec.x;
  this->y = this->y + vec.y;
  this->z = this->z + vec.z;
  return this;
}
me::vec3d* me::vec3d::sub(me::vec3d &vec)
{
  this->x = this->x - vec.x;
  this->y = this->y - vec.y;
  this->z = this->z - vec.z;
  return this;
}
me::vec3d* me::vec3d::mul(me::vec3d &vec)
{
  this->x = this->x * vec.x;
  this->y = this->y * vec.y;
  this->z = this->z * vec.z;
  return this;
}
me::vec3d* me::vec3d::div(me::vec3d &vec)
{
  this->x = this->x / vec.x;
  this->y = this->y / vec.y;
  this->z = this->z / vec.z;
  return this;
}

me::vec3d* me::vec3d::add(double fac)
{
  this->x = this->x + fac;
  this->y = this->y + fac;
  this->z = this->z + fac;
  return this;
}
me::vec3d* me::vec3d::sub(double fac)
{
  this->x = this->x - fac;
  this->y = this->y - fac;
  this->z = this->z - fac;
  return this;
}
me::vec3d* me::vec3d::mul(double fac)
{
  this->x = this->x * fac;
  this->y = this->y * fac;
  this->z = this->z * fac;
  return this;
}
me::vec3d* me::vec3d::div(double fac)
{
  this->x = this->x / fac;
  this->y = this->y / fac;
  this->z = this->z / fac;
  return this;
}

#endif
