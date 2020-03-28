#ifndef VEC_2I_H
  #define VEC_2I_H

me::vec2i::vec2i(int x, int y)
{
  this->x = x;
  this->y = y;
}

void me::vec2i::add(me::vec2i &vec)
{
  this->x+=vec.x;
  this->y+=vec.y;
}
void me::vec2i::sub(me::vec2i &vec)
{
}
void me::vec2i::mul(me::vec2i &vec)
{
}
void me::vec2i::div(me::vec2i &vec)
{
}

#endif
