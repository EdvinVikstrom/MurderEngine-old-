#include "vector2.hpp"

me::vec2 me::vec2::abs() const
{
  real_t x = me::maths::abs(me::vec2::x);
  real_t y = me::maths::abs(me::vec2::y);
  return me::vec2(x, y);
}
me::vec2 me::vec2::floor() const
{
  real_t x = me::maths::floor(me::vec2::x);
  real_t y = me::maths::floor(me::vec2::y);
  return me::vec2(x, y);
}
me::vec2 me::vec2::ceil() const
{
  real_t x = me::maths::ceil(me::vec2::x);
  real_t y = me::maths::ceil(me::vec2::y);
  return me::vec2(x, y);
}
me::vec2 me::vec2::sign() const
{
  real_t x = me::maths::sign(me::vec2::x);
  real_t y = me::maths::sign(me::vec2::y);
  return me::vec2(x, y);
}
me::vec2 me::vec2::round() const
{
  real_t x = me::maths::round(me::vec2::x);
  real_t y = me::maths::round(me::vec2::y);
  return me::vec2(x, y);
}

bool me::vec2::equals(vec2 &vec)
{
  return me::vec2::x == vec.x && me::vec2::y == vec.y;
}

me::vec2& me::vec2::operator+=(vec2 &vec)
{
  me::vec2::x+=vec.x;
  me::vec2::y+=vec.y;
  return *this;
}
me::vec2 me::vec2::operator+(vec2 &vec) const
{
  return vec2(me::vec2::x + vec.x, me::vec2::y + vec.y);
}
me::vec2& me::vec2::operator+=(real_t value)
{
  me::vec2::x+=value;
  me::vec2::y+=value;
  return *this;
}
me::vec2 me::vec2::operator+(real_t value) const
{
  return vec2(me::vec2::x + value, me::vec2::y + value);
}

me::vec2& me::vec2::operator-=(vec2 &vec)
{
  me::vec2::x-=vec.x;
  me::vec2::y-=vec.y;
  return *this;
}
me::vec2 me::vec2::operator-(vec2 &vec) const
{
  return vec2(me::vec2::x - vec.x, me::vec2::y - vec.y);
}
me::vec2& me::vec2::operator-=(real_t value)
{
  me::vec2::x-=value;
  me::vec2::y-=value;
  return *this;
}
me::vec2 me::vec2::operator-(real_t value) const
{
  return vec2(me::vec2::x - value, me::vec2::y - value);
}

me::vec2& me::vec2::operator*=(vec2 &vec)
{
  me::vec2::x*=vec.x;
  me::vec2::y*=vec.y;
  return *this;
}
me::vec2 me::vec2::operator*(vec2 &vec) const
{
  return vec2(me::vec2::x * vec.x, me::vec2::y * vec.y);
}
me::vec2& me::vec2::operator*=(real_t value)
{
  me::vec2::x*=value;
  me::vec2::y*=value;
  return *this;
}
me::vec2 me::vec2::operator*(real_t value) const
{
  return vec2(me::vec2::x * value, me::vec2::y * value);
}

me::vec2& me::vec2::operator/=(vec2 &vec)
{
  me::vec2::x/=vec.x;
  me::vec2::y/=vec.y;
  return *this;
}
me::vec2 me::vec2::operator/(vec2 &vec) const
{
  return vec2(me::vec2::x / vec.x, me::vec2::y / vec.y);
}
me::vec2& me::vec2::operator/=(real_t value)
{
  me::vec2::x/=value;
  me::vec2::y/=value;
  return *this;
}
me::vec2 me::vec2::operator/(real_t value) const
{
  return vec2(me::vec2::x / value, me::vec2::y / value);
}