#ifndef VEC_3I_H
  #define VEC_3I_H

me::vec3i::vec3i(int x, int y, int z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

void me::vec3i::add(me::vec3i &vec)
{
  this->x = this->x + vec.x;
  this->y = this->y + vec.y;
  this->z = this->z + vec.z;
}
void me::vec3i::sub(me::vec3i &vec)
{
  this->x = this->x - vec.x;
  this->y = this->y - vec.y;
  this->z = this->z - vec.z;
}
void me::vec3i::mul(me::vec3i &vec)
{
  this->x = this->x * vec.x;
  this->y = this->y * vec.y;
  this->z = this->z * vec.z;
}
void me::vec3i::div(me::vec3i &vec)
{
  this->x = this->x / vec.x;
  this->y = this->y / vec.y;
  this->z = this->z / vec.z;
}

void me::vec3i::add(int fac)
{
  this->x = this->x + fac;
  this->y = this->y + fac;
  this->z = this->z + fac;
}
void me::vec3i::sub(int fac)
{
  this->x = this->x - fac;
  this->y = this->y - fac;
  this->z = this->z - fac;
}
void me::vec3i::mul(int fac)
{
  this->x = this->x * fac;
  this->y = this->y * fac;
  this->z = this->z * fac;
}
void me::vec3i::div(int fac)
{
  this->x = this->x / fac;
  this->y = this->y / fac;
  this->z = this->z / fac;
}

#endif
