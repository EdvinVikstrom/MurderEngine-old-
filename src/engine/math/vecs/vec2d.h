#ifndef VEC_2D_H
  #define VEC_2D_H

me::vec2d::vec2d(double x, double y)
{
  this->x = x;
  this->y = y;
}

void me::vec2d::add(me::vec2d &vec)
{
  this->x+=vec.x;
  this->y+=vec.y;
}
void me::vec2d::sub(me::vec2d &vec)
{
}
void me::vec2d::mul(me::vec2d &vec)
{
}
void me::vec2d::div(me::vec2d &vec)
{
}

#endif
