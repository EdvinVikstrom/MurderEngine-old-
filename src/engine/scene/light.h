#ifndef LIGHT_H
  #define LIGHT_H

namespace me {

  struct light {
    std::string identifier;
    double power;
    double size;
    me::vec4f* rgba;
    light(std::string identifier, double power, double size, me::vec4f* rgba)
    {
      this->identifier = identifier;
      this->power = power;
      this->size = size;
      this->rgba = rgba;
    }
    light() { }
  };

  struct light_item : item {
    me::light* light;
    light_item(std::string identifier, me::vec3d* position, me::vec3d* rotation, me::vec3d* scale, me::light* light) :
    item(ME_ITEM_TYPE_LIGHT, identifier, position, rotation, scale)
    {
      this->light = light;
    }
  };

};

#endif
