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
  this->x+=vec.x;
  this->y+=vec.y;
  this->z+=vec.z;
}
void me::vec3i::sub(me::vec3i &vec)
{
}
void me::vec3i::mul(me::vec3i &vec)
{
}
void me::vec3i::div(me::vec3i &vec)
{
}

#endif
