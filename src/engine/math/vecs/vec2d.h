#ifndef VEC_2D_H
  #define VEC_2D_H

me::vec2d::vec2d(double x, double y)
{
  this->x = x;
  this->y = y;
}

void me::vec2d::add(me::vec2d &vec)
{
  this->x = this->x + vec.x;
  this->y = this->y + vec.y;
}
void me::vec2d::sub(me::vec2d &vec)
{
  this->x = this->x - vec.x;
  this->y = this->y - vec.y;
}
void me::vec2d::mul(me::vec2d &vec)
{
  this->x = this->x * vec.x;
  this->y = this->y * vec.y;
}
void me::vec2d::div(me::vec2d &vec)
{
  this->x = this->x / vec.x;
  this->y = this->y / vec.y;
}

void me::vec2d::add(double fac)
{
  this->x = this->x + fac;
  this->y = this->y + fac;
}
void me::vec2d::sub(double fac)
{
  this->x = this->x - fac;
  this->y = this->y - fac;
}
void me::vec2d::mul(double fac)
{
  this->x = this->x * fac;
  this->y = this->y * fac;
}
void me::vec2d::div(double fac)
{
  this->x = this->x / fac;
  this->y = this->y / fac;
}


#endif
