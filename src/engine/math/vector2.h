#ifndef VECTOR2_H
  #define VECTOR2_H

#include "maths.h"

namespace me {

  struct vec2 {

    enum axis {
      X, Y
    };

    union {
      struct {
        real_t x, y;
      };
      real_t axis[2];
    };

    vec2(real_t x, real_t y)
    {
      this->x = x;
      this->y = y;
    }

    vec2(real_t value)
    {
      this->x = value;
      this->y = value;
    }

    vec2()
    {
      this->x = real_t(0);
      this->y = real_t(0);
    }

    vec2 abs() const;
    vec2 floor() const;
    vec2 ceil() const;
    vec2 sign() const;
    vec2 round() const;

    bool equals(vec2 &vec);

    vec2& operator+=(vec2 &vec);
    vec2 operator+(vec2 &vec) const;
    vec2& operator+=(real_t value);
    vec2 operator+(real_t value) const;

    vec2& operator-=(vec2 &vec);
    vec2 operator-(vec2 &vec) const;
    vec2& operator-=(real_t value);
    vec2 operator-(real_t value) const;

    vec2& operator*=(vec2 &vec);
    vec2 operator*(vec2 &vec) const;
    vec2& operator*=(real_t value);
    vec2 operator*(real_t value) const;

    vec2& operator/=(vec2 &vec);
    vec2 operator/(vec2 &vec) const;
    vec2& operator/=(real_t value);
    vec2 operator/(real_t value) const;

    inline real_t& operator[](unsigned int index)
    {
      return axis[index];
    }

    inline bool operator==(vec2 &vec) { return equals(vec); }
    inline bool operator!=(vec2 &vec) { return !equals(vec); }

  };

};

#endif
