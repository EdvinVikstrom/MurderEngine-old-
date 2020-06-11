#ifndef LIGHT_H
  #define LIGHT_H

#include "../math/transform.hpp"

namespace me {

  enum LightType : unsigned char {
    LIGHT_TYPE_POINT,
    LIGHT_TYPE_SUN,
    LIGHT_TYPE_SPOT,
    LIGHT_TYPE_AREA
  };

  struct LightInfo {
    uint32_t data[4];
    std::string source;
    std::string identifier;
    me::metadata* metadata = new me::metadata;
    LightType type;
  };

  struct Light {

    me::transform transform;
    me::vec3 rgb;

    LightInfo info;

    Light(me::transform transform, me::vec3 rgb, LightInfo info)
    {
      this->transform = transform;
      this->rgb = rgb;
      this->info = info;
    }

    Light() { }

    ~Light()
    {
    }

  };

};

#endif