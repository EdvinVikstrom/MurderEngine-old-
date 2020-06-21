#ifndef CAMERA_HPP
  #define CAMERA_HPP

#include "../math/matrix.hpp"
#include "../math/transform.hpp"

namespace me {

  enum CameraProjection {
    PROJ_PERSPECTIVE,
    PROJ_FRUSTUM,
    PROJ_ORTHOGRAPHIC,
    PROJ_VIEW_2D,
    PROJ_ENC_VIEW_2D
  };

  struct CameraInfo {
    uint32_t data[4];
    std::string identifier = "?";
    CameraProjection projection = PROJ_PERSPECTIVE;
  };

  struct Camera {

    me::transform transform;
    real_t* projMatrix;
    real_t* viewMatrix;

    float focalLength;
    float aspectRatio;
    float znear, zfar;
    uint32_t width, height;

    CameraInfo info;

    inline void setupProjMatrix()
    {
      std::cout << "a\n";
      me::maths::identify_mat4(projMatrix);
      std::cout << "b\n";
      if (info.projection == PROJ_PERSPECTIVE)
        me::maths::perspective_mat4(projMatrix, focalLength, aspectRatio, znear, zfar);
        std::cout << "c\n";
    }

    inline void setupViewMatrix()
    {
      me::maths::identify_mat4(viewMatrix);
    }

    Camera(me::transform transform, float focalLength, float aspectRatio, float znear, float zfar, uint32_t width, uint32_t height, CameraInfo info)
    {
      std::cout << "t\n";
      this->transform = transform;
      std::cout << "t\n";
      this->focalLength = focalLength;
      this->aspectRatio = aspectRatio;
      this->znear = znear;
      this->zfar = zfar;
      this->width = width;
      this->height = height;
      this->info = info;
      projMatrix = new real_t[16];
      viewMatrix = new real_t[16];
      setupProjMatrix();
      setupViewMatrix();
    }

    Camera() { }

    ~Camera()
    {
    }

  };

};

#endif
