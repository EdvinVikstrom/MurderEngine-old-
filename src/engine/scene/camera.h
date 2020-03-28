#ifndef CAMERA_H
  #define CAMERA_H

#define ME_CAMERA_PERSPECTIVE              45
#define ME_CAMERA_2D_VIEW                  47

namespace me {

  struct camera {
    std::string identifier;
    me::vec3d position, rotation;
    unsigned int type; // TODO: Find the right name
    float aspectRatio;
    /* FOV (Field Of View) */
    float focalLength;
    double znear, zfar;

    camera(std::string identifier, me::vec3d position, me::vec3d rotation, unsigned int type, float aspectRatio, float focalLength, double znear, double zfar)
    {
      this->identifier = identifier;
      this->position = position;
      this->rotation = rotation;
      this->type = type;
      this->aspectRatio = aspectRatio;
      this->focalLength = focalLength;
      this->znear = znear;
      this->zfar = zfar;
    }

    camera() { }

  };

  struct camera_item : item {
    unsigned int camera;
    camera_item(std::string identifier, me::vec3d position, me::vec3d rotation, me::vec3d scale, me::vec3d origin, unsigned int camera) : item(ME_ITEM_TYPE_CAMERA, identifier, position, rotation, scale, origin)
    {
      this->camera = camera;
    }
  };

};

#endif
