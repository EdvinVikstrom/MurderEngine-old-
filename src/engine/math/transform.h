#ifndef TRANSFORM_H
  #define TRANSFORM_H

#include "vectors.h"
#include "maths.h"

#include <iostream> // remove

namespace me {

  struct transform {

    me::vec3d location, rotation, scale;

    transform(me::vec3d location, me::vec3d rotation, me::vec3d scale)
    {
      this->location = location;
      this->rotation = rotation;
      this->scale = scale;
    }

    transform(float** matrix, unsigned int rows, unsigned int columns)
    {
      location.x = matrix[0][3];
      location.y = matrix[1][3];
      location.z = matrix[2][3];

      rotation.x = maths::atan2d(matrix[2][1], matrix[2][2]);
      rotation.y = maths::atan2d(-matrix[2][0], maths::sqrtd(maths::powd(matrix[2][1], 2) + maths::powd(matrix[2][2], 2)));
      rotation.z = maths::atan2d(matrix[1][0], matrix[0][0]);

      scale.x = matrix[0][0];
      scale.y = matrix[1][1];
      scale.z = matrix[2][2];

      std::cout << location.x << ", " << location.y << ", " << location.z << " | " <<
      rotation.x << ", " << rotation.y << ", " << rotation.z << " | " <<
      scale.x << ", " << scale.y << ", " << scale.z <<
      "\n";
    }

    transform() { }

  };

};

#endif
