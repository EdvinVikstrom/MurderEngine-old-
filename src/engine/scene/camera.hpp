#ifndef CAMERA_H
  #define CAMERA_H

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
    std::string source;
    std::string identifier;
    me::metadata* metadata = new me::metadata;
    CameraProjection projection;
  };
  
  struct Camera {
    
    me::transform transform;
    
    float focalLength;
    float aspectRatio;
    float znear, zfar;
    uint32_t width, height;
    
    CameraInfo info;
    
    Camera(me::transform transform, float focalLength, float aspectRatio, float znear, float zfar, uint32_t width, uint32_t height, CameraInfo info)
    {
      this->transform = transform;
      this->focalLength = focalLength;
      this->aspectRatio = aspectRatio;
      this->znear = znear;
      this->zfar = zfar;
      this->width = width;
      this->height = height;
      this->info = info;
    }
    
    Camera() { }
    
    ~Camera()
    {
    }
    
  };
  
};

#endif
