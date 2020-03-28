#ifndef VEC_2F_H
  #define VEC_2F_H

me::vec2f::vec2f(float x, float y)
{
  this->x = x;
  this->y = y;
}

me::vec2f* me::vec2f::add(me::vec2f &vec)
{
  this->x = this->x + vec.x;
  this->y = this->y + vec.y;
  return this;
}
me::vec2f* me::vec2f::sub(me::vec2f &vec)
{
  this->x = this->x - vec.x;
  this->y = this->y - vec.y;
  return this;
}
me::vec2f* me::vec2f::mul(me::vec2f &vec)
{
  this->x = this->x * vec.x;
  this->y = this->y * vec.y;
  return this;
}
me::vec2f* me::vec2f::div(me::vec2f &vec)
{
  this->x = this->x / vec.x;
  this->y = this->y / vec.y;
  return this;
}

me::vec2f* me::vec2f::add(float fac)
{
  this->x = this->x + fac;
  this->y = this->y + fac;
  return this;
}
me::vec2f* me::vec2f::sub(float fac)
{
  this->x = this->x - fac;
  this->y = this->y - fac;
  return this;
}
me::vec2f* me::vec2f::mul(float fac)
{
  this->x = this->x * fac;
  this->y = this->y * fac;
  return this;
}
me::vec2f* me::vec2f::div(float fac)
{
  this->x = this->x / fac;
  this->y = this->y / fac;
  return this;
}

#endif
