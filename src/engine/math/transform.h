#ifndef TRANSFORM_H
  #define TRANSFORM_H

#include "matrix.h"
#include "maths.h"

namespace me {

  struct transform {

    me::vec3 location, rotation, scale;
    me::maths::mat4 matrix;

    void updateMatrix()
    {
      me::maths::identify(matrix);
      me::maths::translate(matrix, location.x, location.y, location.z);
      me::maths::scale(matrix, scale.x, scale.y, scale.z);
      me::maths::rotate(matrix, rotation.x, rotation.y, rotation.z);
    }

    transform(me::vec3 location, me::vec3 rotation, me::vec3 scale)
    {
      this->location = location;
      this->rotation = rotation;
      this->scale = scale;
      updateMatrix();
    }
    transform(me::maths::mat4 matrix)
    {
      this->matrix = matrix;
    }

    transform(float** matrix, unsigned int rows, unsigned int columns)
    {
    }

    transform() { }

  };

};

#endif
