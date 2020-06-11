#ifndef VECTOR3_H
  #define VECTOR3_H

#include "maths.hpp"

namespace me {

  struct vec3 {

    enum axis {
      X, Y, Z
    };

    union {
      struct {
        real_t x, y, z;
      };
      real_t axis[3];
    };

    vec3(real_t x, real_t y, real_t z)
    {
      this->x = x;
      this->y = y;
      this->z = z;
    }

    vec3(real_t value)
    {
      this->x = value;
      this->y = value;
      this->z = value;
    }

    vec3(const me::vec3 &vec)
    {
      this->x = vec.x;
      this->y = vec.y;
      this->z = vec.z;
    }

    vec3()
    {
      this->x = real_t(0);
      this->y = real_t(0);
      this->z = real_t(0);
    }

    vec3 abs() const;
    vec3 floor() const;
    vec3 ceil() const;
    vec3 sign() const;
    vec3 round() const;

    bool equals(vec3 &vec);

    vec3& operator+=(vec3 vec);
    vec3 operator+(vec3 vec) const;
    vec3& operator+=(real_t value);
    vec3 operator+(real_t value) const;

    vec3& operator-=(vec3 vec);
    vec3 operator-(vec3 vec) const;
    vec3& operator-=(real_t value);
    vec3 operator-(real_t value) const;

    vec3& operator*=(vec3 vec);
    vec3 operator*(vec3 vec) const;
    vec3& operator*=(real_t value);
    vec3 operator*(real_t value) const;

    vec3& operator/=(vec3 vec);
    vec3 operator/(vec3 vec) const;
    vec3& operator/=(real_t value);
    vec3 operator/(real_t value) const;

    inline real_t& operator[](unsigned int index)
    {
      return axis[index];
    }

    inline bool operator==(vec3 &vec) { return equals(vec); }
    inline bool operator!=(vec3 &vec) { return !equals(vec); }

  };

};

#endif