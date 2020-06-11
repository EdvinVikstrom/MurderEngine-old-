#include "vector4.hpp"

me::vec4 me::vec4::abs() const
{
  real_t x = me::maths::abs(me::vec4::x);
  real_t y = me::maths::abs(me::vec4::y);
  real_t z = me::maths::abs(me::vec4::z);
  real_t w = me::maths::abs(me::vec4::w);
  return me::vec4(x, y, z, w);
}
me::vec4 me::vec4::floor() const
{
  real_t x = me::maths::floor(me::vec4::x);
  real_t y = me::maths::floor(me::vec4::y);
  real_t z = me::maths::floor(me::vec4::z);
  real_t w = me::maths::floor(me::vec4::w);
  return me::vec4(x, y, z, w);
}
me::vec4 me::vec4::ceil() const
{
  real_t x = me::maths::ceil(me::vec4::x);
  real_t y = me::maths::ceil(me::vec4::y);
  real_t z = me::maths::ceil(me::vec4::z);
  real_t w = me::maths::ceil(me::vec4::w);
  return me::vec4(x, y, z, w);
}
me::vec4 me::vec4::sign() const
{
  real_t x = me::maths::sign(me::vec4::x);
  real_t y = me::maths::sign(me::vec4::y);
  real_t z = me::maths::sign(me::vec4::z);
  real_t w = me::maths::sign(me::vec4::w);
  return me::vec4(x, y, z, w);
}
me::vec4 me::vec4::round() const
{
  real_t x = me::maths::round(me::vec4::x);
  real_t y = me::maths::round(me::vec4::y);
  real_t z = me::maths::round(me::vec4::z);
  real_t w = me::maths::round(me::vec4::w);
  return me::vec4(x, y, z, w);
}

bool me::vec4::equals(vec4 &vec)
{
  return me::vec4::x == vec.x && me::vec4::y == vec.y && me::vec4::z == vec.z && me::vec4::w == vec.w;
}

me::vec4& me::vec4::operator+=(vec4 &vec)
{
  me::vec4::x+=vec.x;
  me::vec4::y+=vec.y;
  me::vec4::z+=vec.z;
  me::vec4::w+=vec.w;
  return *this;
}
me::vec4 me::vec4::operator+(vec4 &vec) const
{
  return vec4(me::vec4::x + vec.x, me::vec4::y + vec.y, me::vec4::z + vec.z, me::vec4::w + vec.w);
}
me::vec4& me::vec4::operator+=(real_t value)
{
  me::vec4::x+=value;
  me::vec4::y+=value;
  me::vec4::z+=value;
  me::vec4::w+=value;
  return *this;
}
me::vec4 me::vec4::operator+(real_t value) const
{
  return vec4(me::vec4::x + value, me::vec4::y + value, me::vec4::z + value, me::vec4::w + value);
}

me::vec4& me::vec4::operator-=(vec4 &vec)
{
  me::vec4::x-=vec.x;
  me::vec4::y-=vec.y;
  me::vec4::z-=vec.z;
  me::vec4::w-=vec.w;
  return *this;
}
me::vec4 me::vec4::operator-(vec4 &vec) const
{
  return vec4(me::vec4::x - vec.x, me::vec4::y - vec.y, me::vec4::z - vec.z, me::vec4::w - vec.w);
}
me::vec4& me::vec4::operator-=(real_t value)
{
  me::vec4::x-=value;
  me::vec4::y-=value;
  me::vec4::z-=value;
  me::vec4::w-=value;
  return *this;
}
me::vec4 me::vec4::operator-(real_t value) const
{
  return vec4(me::vec4::x - value, me::vec4::y - value, me::vec4::z - value, me::vec4::w - value);
}

me::vec4& me::vec4::operator*=(vec4 &vec)
{
  me::vec4::x*=vec.x;
  me::vec4::y*=vec.y;
  me::vec4::z*=vec.z;
  me::vec4::w*=vec.w;
  return *this;
}
me::vec4 me::vec4::operator*(vec4 &vec) const
{
  return vec4(me::vec4::x * vec.x, me::vec4::y * vec.y, me::vec4::z * vec.z, me::vec4::w * vec.w);
}
me::vec4& me::vec4::operator*=(real_t value)
{
  me::vec4::x*=value;
  me::vec4::y*=value;
  me::vec4::z*=value;
  me::vec4::w*=value;
  return *this;
}
me::vec4 me::vec4::operator*(real_t value) const
{
  return vec4(me::vec4::x * value, me::vec4::y * value, me::vec4::z * value, me::vec4::w * value);
}

me::vec4& me::vec4::operator/=(vec4 &vec)
{
  me::vec4::x/=vec.x;
  me::vec4::y/=vec.y;
  me::vec4::z/=vec.z;
  me::vec4::w/=vec.w;
  return *this;
}
me::vec4 me::vec4::operator/(vec4 &vec) const
{
  return vec4(me::vec4::x / vec.x, me::vec4::y / vec.y, me::vec4::z / vec.z, me::vec4::w / vec.w);
}
me::vec4& me::vec4::operator/=(real_t value)
{
  me::vec4::x/=value;
  me::vec4::y/=value;
  me::vec4::z/=value;
  me::vec4::w/=value;
  return *this;
}
me::vec4 me::vec4::operator/(real_t value) const
{
  return vec4(me::vec4::x / value, me::vec4::y / value, me::vec4::z / value, me::vec4::w / value);
}