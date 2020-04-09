#include "vector3.h"

me::vec3 me::vec3::abs() const
{
  real_t x = me::maths::abs(me::vec3::x);
  real_t y = me::maths::abs(me::vec3::y);
  real_t z = me::maths::abs(me::vec3::z);
  return me::vec3(x, y, z);
}
me::vec3 me::vec3::floor() const
{
  real_t x = me::maths::floor(me::vec3::x);
  real_t y = me::maths::floor(me::vec3::y);
  real_t z = me::maths::floor(me::vec3::z);
  return me::vec3(x, y, z);
}
me::vec3 me::vec3::ceil() const
{
  real_t x = me::maths::ceil(me::vec3::x);
  real_t y = me::maths::ceil(me::vec3::y);
  real_t z = me::maths::ceil(me::vec3::z);
  return me::vec3(x, y, z);
}
me::vec3 me::vec3::sign() const
{
  real_t x = me::maths::sign(me::vec3::x);
  real_t y = me::maths::sign(me::vec3::y);
  real_t z = me::maths::sign(me::vec3::z);
  return me::vec3(x, y, z);
}
me::vec3 me::vec3::round() const
{
  real_t x = me::maths::round(me::vec3::x);
  real_t y = me::maths::round(me::vec3::y);
  real_t z = me::maths::round(me::vec3::z);
  return me::vec3(x, y, z);
}

bool me::vec3::equals(vec3 &vec)
{
  return me::vec3::x == vec.x && me::vec3::y == vec.y && me::vec3::z == vec.z;
}

me::vec3& me::vec3::operator+=(vec3 &vec)
{
  me::vec3::x+=vec.x;
  me::vec3::y+=vec.y;
  me::vec3::z+=vec.z;
  return *this;
}
me::vec3 me::vec3::operator+(vec3 &vec) const
{
  return vec3(me::vec3::x + vec.x, me::vec3::y + vec.y, me::vec3::z + vec.z);
}
me::vec3& me::vec3::operator+=(real_t value)
{
  me::vec3::x+=value;
  me::vec3::y+=value;
  me::vec3::z+=value;
  return *this;
}
me::vec3 me::vec3::operator+(real_t value) const
{
  return vec3(me::vec3::x + value, me::vec3::y + value, me::vec3::z + value);
}

me::vec3& me::vec3::operator-=(vec3 &vec)
{
  me::vec3::x-=vec.x;
  me::vec3::y-=vec.y;
  me::vec3::z-=vec.z;
  return *this;
}
me::vec3 me::vec3::operator-(vec3 &vec) const
{
  return vec3(me::vec3::x - vec.x, me::vec3::y - vec.y, me::vec3::z - vec.z);
}
me::vec3& me::vec3::operator-=(real_t value)
{
  me::vec3::x-=value;
  me::vec3::y-=value;
  me::vec3::z-=value;
  return *this;
}
me::vec3 me::vec3::operator-(real_t value) const
{
  return vec3(me::vec3::x - value, me::vec3::y - value, me::vec3::z - value);
}

me::vec3& me::vec3::operator*=(vec3 &vec)
{
  me::vec3::x*=vec.x;
  me::vec3::y*=vec.y;
  me::vec3::z*=vec.z;
  return *this;
}
me::vec3 me::vec3::operator*(vec3 &vec) const
{
  return vec3(me::vec3::x * vec.x, me::vec3::y * vec.y, me::vec3::z * vec.z);
}
me::vec3& me::vec3::operator*=(real_t value)
{
  me::vec3::x*=value;
  me::vec3::y*=value;
  me::vec3::z*=value;
  return *this;
}
me::vec3 me::vec3::operator*(real_t value) const
{
  return vec3(me::vec3::x * value, me::vec3::y * value, me::vec3::z * value);
}

me::vec3& me::vec3::operator/=(vec3 &vec)
{
  me::vec3::x/=vec.x;
  me::vec3::y/=vec.y;
  me::vec3::z/=vec.z;
  return *this;
}
me::vec3 me::vec3::operator/(vec3 &vec) const
{
  return vec3(me::vec3::x / vec.x, me::vec3::y / vec.y, me::vec3::z / vec.z);
}
me::vec3& me::vec3::operator/=(real_t value)
{
  me::vec3::x/=value;
  me::vec3::y/=value;
  me::vec3::z/=value;
  return *this;
}
me::vec3 me::vec3::operator/(real_t value) const
{
  return vec3(me::vec3::x / value, me::vec3::y / value, me::vec3::z / value);
}
