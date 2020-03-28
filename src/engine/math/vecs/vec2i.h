#ifndef VEC_2I_H
  #define VEC_2I_H

me::vec2i::vec2i(int x, int y)
{
  this->x = x;
  this->y = y;
}

me::vec2i* me::vec2i::add(me::vec2i &vec)
{
  this->x = this->x + vec.x;
  this->y = this->y + vec.y;
  return this;
}
me::vec2i* me::vec2i::sub(me::vec2i &vec)
{
  this->x = this->x - vec.x;
  this->y = this->y - vec.y;
  return this;
}
me::vec2i* me::vec2i::mul(me::vec2i &vec)
{
  this->x = this->x * vec.x;
  this->y = this->y * vec.y;
  return this;
}
me::vec2i* me::vec2i::div(me::vec2i &vec)
{
  this->x = this->x / vec.x;
  this->y = this->y / vec.y;
  return this;
}

me::vec2i* me::vec2i::add(int fac)
{
  this->x = this->x + fac;
  this->y = this->y + fac;
  return this;
}
me::vec2i* me::vec2i::sub(int fac)
{
  this->x = this->x - fac;
  this->y = this->y - fac;
  return this;
}
me::vec2i* me::vec2i::mul(int fac)
{
  this->x = this->x * fac;
  this->y = this->y * fac;
  return this;
}
me::vec2i* me::vec2i::div(int fac)
{
  this->x = this->x / fac;
  this->y = this->y / fac;
  return this;
}

#endif
