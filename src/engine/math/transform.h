#ifndef TRANSFORM_H
  #define TRANSFORM_H

#include "vectors.h"
#include "maths.h"

#include <iostream> // remove

namespace me {

  struct transform {

    me::vec3 location, rotation, scale;
    float* matrix;

    transform(me::vec3 location, me::vec3 rotation, me::vec3 scale)
    {
      this->location = location;
      this->rotation = rotation;
      this->scale = scale;
      matrix = new float[4*4];
    }

    float* to_matrix()
    {
      matrix[3] = location.x;
      matrix[7] = location.y;
      matrix[11] = location.z;

      matrix[0] = maths::cos(rotation.x);
      matrix[5] = maths::sin(rotation.y);
      matrix[10] = maths::sin(rotation.z);
      return matrix;
    }

    transform(float** matrix, unsigned int rows, unsigned int columns)
    {
    }

    transform() { }

  };

};

#endif
