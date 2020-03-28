#ifndef VEC_2F_H
  #define VEC_2F_H

me::vec2f::vec2f(float x, float y)
{
  this->x = x;
  this->y = y;
}

void me::vec2f::add(me::vec2f &vec)
{
  this->x = this->x + vec.x;
  this->y = this->y + vec.y;
}
void me::vec2f::sub(me::vec2f &vec)
{
  this->x = this->x - vec.x;
  this->y = this->y - vec.y;
}
void me::vec2f::mul(me::vec2f &vec)
{
  this->x = this->x * vec.x;
  this->y = this->y * vec.y;
}
void me::vec2f::div(me::vec2f &vec)
{
  this->x = this->x / vec.x;
  this->y = this->y / vec.y;
}

#endif
