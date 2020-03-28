#ifndef VEC_4D_H
  #define VEC_4D_H

me::vec4d::vec4d(double x, double y, double z, double w)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

void me::vec4d::add(me::vec4d &vec)
{
  this->x+=vec.x;
  this->y+=vec.y;
  this->z+=vec.z;
  this->w+=vec.w;
}
void me::vec4d::sub(me::vec4d &vec)
{
}
void me::vec4d::mul(me::vec4d &vec)
{
}
void me::vec4d::div(me::vec4d &vec)
{
}

#endif
