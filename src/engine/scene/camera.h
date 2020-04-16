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
    me::vec3 position;
    me::vec3 rotation;

    me::maths::mat4 rotationX_matrix;
    me::maths::mat4 rotationY_matrix;
    me::maths::mat4 rotationZ_matrix;

    me::maths::mat4 view_matrix;
    me::maths::mat4 projection_matrix;

    camera(std::string identifier, camera_type type, float focalLength, float aspectRatio, float znear, float zfar, me::vec3 position, me::vec3 rotation)
    {
      this->identifier = identifier;
      this->type = type;
      this->focalLength = focalLength;
      this->aspectRatio = aspectRatio;
      this->znear = znear;
      this->zfar = zfar;
      this->position = position;
      this->rotation = rotation;

      me::maths::identify(rotationX_matrix);
      me::maths::identify(rotationY_matrix);
      me::maths::identify(rotationZ_matrix);

      me::maths::identify(view_matrix);
      me::maths::translate(view_matrix, position.x, position.y, position.z);
      me::maths::identify(projection_matrix);
      if (type==camera_type::PERSPECTIVE)
        me::maths::perspective(projection_matrix, focalLength, aspectRatio, znear, zfar);
      else if (type==camera_type::FRUSTUM)
        me::maths::frustum(projection_matrix, -aspectRatio, aspectRatio, -1.0F, 1.0F, znear, zfar);
      else if (type==camera_type::ORTHOGRAPHIC)
        me::maths::orthographic(projection_matrix, -aspectRatio, aspectRatio, -1.0F, 1.0F, znear, zfar);
    }

    camera() { }

    void update_matrix()
    {
      //me::maths::identify(view_matrix);
      me::maths::rotate(view_matrix, -rotation.x, -rotation.y, -rotation.z);
      me::maths::translate(view_matrix, -position.x, -position.y, -position.z);
    }

    void move(float x, float y, float z)
    {
      position.x+=x;
      position.y+=y;
      position.z+=z;
    }

    void rotate(float yaw, float pitch, float roll)
    {
      rotation.x+=pitch;
      rotation.y+=yaw;
      rotation.z+=roll;
    }

  };

};

#endif
