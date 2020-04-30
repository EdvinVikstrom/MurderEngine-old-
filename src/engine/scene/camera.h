#ifndef CAMERA_H
  #define CAMERA_H

#include "../math/matrix.h"

namespace me {

  enum CameraProjection {
    PROJ_PERSPECTIVE,
    PROJ_FRUSTUM,
    PROJ_ORTHOGRAPHIC,
    PROJ_VIEW_2D,
    PROJ_ENC_VIEW_2D
  };

  struct Camera {
    std::string identifier;
    CameraProjection projection;
    float focalLength;
    float aspectRatio;
    float znear, zfar;
    uint32_t width, height;
    me::vec3 position;
    me::vec3 rotation;

    me::maths::mat4 view_matrix;
    me::maths::mat4 projection_matrix;

    Camera(std::string identifier, CameraProjection projection, float focalLength, float aspectRatio, float znear, float zfar, uint32_t width, uint32_t height, me::vec3 position, me::vec3 rotation)
    {
      this->identifier = identifier;
      this->projection = projection;
      this->focalLength = focalLength;
      this->aspectRatio = aspectRatio;
      this->znear = znear;
      this->zfar = zfar;
      this->width = width;
      this->height = height;
      this->position = position;
      this->rotation = rotation;

      me::maths::identify(view_matrix);
      me::maths::translate(view_matrix, position.x, position.y, position.z);
      me::maths::identify(projection_matrix);
      if (projection==CameraProjection::PROJ_PERSPECTIVE)
        me::maths::perspective(projection_matrix, focalLength, aspectRatio, znear, zfar);
      else if (projection==CameraProjection::PROJ_FRUSTUM)
        me::maths::frustum(projection_matrix, -aspectRatio, aspectRatio, -1.0F, 1.0F, znear, zfar);
      else if (projection==CameraProjection::PROJ_ORTHOGRAPHIC)
        me::maths::orthographic(projection_matrix, -aspectRatio, aspectRatio, -1.0F, 1.0F, znear, zfar);
      else if (projection==CameraProjection::PROJ_VIEW_2D)
      {
        /*
        projection_matrix.m00(-1);
        projection_matrix.m01(-1);
        projection_matrix.m02(-1);
        projection_matrix.m03(-1);
        projection_matrix.m10(-1);
        projection_matrix.m11(-1);
        projection_matrix.m12(-1);
        projection_matrix.m13(-1);
        projection_matrix.m20(-1);
        projection_matrix.m21(-1);
        projection_matrix.m22(-1);
        projection_matrix.m23(-1);
        projection_matrix.m30(-1);
        projection_matrix.m31(-1);
        projection_matrix.m32(-1);
        projection_matrix.m33(-1);
        */
        me::maths::orthographic(projection_matrix, 0, width, height, 0, znear, zfar);
      }
    }

    Camera() { }

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
