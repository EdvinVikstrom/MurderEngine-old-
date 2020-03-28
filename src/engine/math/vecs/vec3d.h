#ifndef VEC_3D_H
  #define VEC_3D_H

me::vec3d::vec3d(double x, double y, double z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

void me::vec3d::add(me::vec3d &vec)
{
  this->x+=vec.x;
  this->y+=vec.y;
  this->z+=vec.z;
}
void me::vec3d::sub(me::vec3d &vec)
{
}
void me::vec3d::mul(me::vec3d &vec)
{
}
void me::vec3d::div(me::vec3d &vec)
{
}

#endif
