#ifndef CAMERA_H
  #define CAMERA_H

#include "../math/matrix.h"

namespace me {

  enum camera_type {
    PERSPECTIVE,
    FRUSTUM,
    ORTHOGRAPHIC,
    VIEW_2D,
    ENC_VIEW_2D
  };

  struct camera {
    std::string identifier;
    camera_type type;
    float focalLength;
    float aspectRatio;
    float znear, zfar;
    me::transform transform;

    me::maths::mat4 view_matrix;
    me::maths::mat4 projection_matrix;

    camera(std::string identifier, camera_type type, float focalLength, float aspectRatio, float znear, float zfar, me::transform transform)
    {
      this->identifier = identifier;
      this->type = type;
      this->focalLength = focalLength;
      this->aspectRatio = aspectRatio;
      this->znear = znear;
      this->zfar = zfar;
      this->transform = transform;

      me::maths::identify(view_matrix);
      me::maths::translate(view_matrix, transform.location.x, transform.location.y, transform.location.z);
      me::maths::identify(projection_matrix);
      if (type==camera_type::PERSPECTIVE)
        me::maths::perspective(projection_matrix, focalLength, aspectRatio, znear, zfar);
      else if (type==camera_type::FRUSTUM)
        me::maths::frustum(projection_matrix, -aspectRatio, aspectRatio, -1.0F, 1.0F, znear, zfar);
      else if (type==camera_type::ORTHOGRAPHIC)
        me::maths::orthographic(projection_matrix, -aspectRatio, aspectRatio, -1.0F, 1.0F, znear, zfar);
    }

    camera() { }

  };

};

#endif
