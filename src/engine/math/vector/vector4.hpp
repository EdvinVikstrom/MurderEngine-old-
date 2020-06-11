#ifndef VECTOR4_H
  #define VECTOR4_H

#include "maths.hpp"

namespace me {

  struct vec4 {

    enum axis {
      X, Y, Z, W
    };

    union {
      struct {
        real_t x, y, z, w;
      };
      real_t axis[4];
    };

    vec4(real_t x, real_t y, real_t z, real_t w)
    {
      this->x = x;
      this->y = y;
      this->z = z;
      this->w = w;
    }

    vec4(real_t value)
    {
      this->x = value;
      this->y = value;
      this->z = value;
      this->w = value;
    }

    vec4()
    {
      this->x = real_t(0);
      this->y = real_t(0);
      this->z = real_t(0);
      this->w = real_t(0);
    }

    vec4 abs() const;
    vec4 floor() const;
    vec4 ceil() const;
    vec4 sign() const;
    vec4 round() const;

    bool equals(vec4 &vec);

    vec4& operator+=(vec4 &vec);
    vec4 operator+(vec4 &vec) const;
    vec4& operator+=(real_t value);
    vec4 operator+(real_t value) const;

    vec4& operator-=(vec4 &vec);
    vec4 operator-(vec4 &vec) const;
    vec4& operator-=(real_t value);
    vec4 operator-(real_t value) const;

    vec4& operator*=(vec4 &vec);
    vec4 operator*(vec4 &vec) const;
    vec4& operator*=(real_t value);
    vec4 operator*(real_t value) const;

    vec4& operator/=(vec4 &vec);
    vec4 operator/(vec4 &vec) const;
    vec4& operator/=(real_t value);
    vec4 operator/(real_t value) const;

    inline real_t& operator[](unsigned int index)
    {
      return axis[index];
    }

    inline bool operator==(vec4 &vec) { return equals(vec); }
    inline bool operator!=(vec4 &vec) { return !equals(vec); }

  };

};

#endif