#ifndef VEC_4I_H
  #define VEC_4I_H

me::vec4i::vec4i(int x, int y, int z, int w)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

void me::vec4i::add(me::vec4i &vec)
{
  this->x = this->x + vec.x;
  this->y = this->y + vec.y;
  this->z = this->z + vec.z;
  this->w = this->w + vec.w;
}
void me::vec4i::sub(me::vec4i &vec)
{
  this->x = this->x - vec.x;
  this->y = this->y - vec.y;
  this->z = this->z - vec.z;
  this->w = this->w - vec.w;
}
void me::vec4i::mul(me::vec4i &vec)
{
  this->x = this->x * vec.x;
  this->y = this->y * vec.y;
  this->z = this->z * vec.z;
  this->w = this->w * vec.w;
}
void me::vec4i::div(me::vec4i &vec)
{
  this->x = this->x / vec.x;
  this->y = this->y / vec.y;
  this->z = this->z / vec.z;
  this->w = this->w / vec.w;
}

void me::vec4i::add(int fac)
{
  this->x = this->x + fac;
  this->y = this->y + fac;
  this->z = this->z + fac;
  this->w = this->w + fac;
}
void me::vec4i::sub(int fac)
{
  this->x = this->x - fac;
  this->y = this->y - fac;
  this->z = this->z - fac;
  this->w = this->w - fac;
}
void me::vec4i::mul(int fac)
{
  this->x = this->x * fac;
  this->y = this->y * fac;
  this->z = this->z * fac;
  this->w = this->w * fac;
}
void me::vec4i::div(int fac)
{
  this->x = this->x / fac;
  this->y = this->y / fac;
  this->z = this->z / fac;
  this->w = this->w / fac;
}

#endif
