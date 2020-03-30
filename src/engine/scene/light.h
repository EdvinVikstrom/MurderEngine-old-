#ifndef LIGHT_H
  #define LIGHT_H

namespace me {

  struct light : mem_utils {
    std::string identifier;
    double power;
    double size;
    me::vec4f rgba;
    light(std::string identifier, double power, double size, me::vec4f rgba)
    {
      this->identifier = identifier;
      this->power = power;
      this->size = size;
      this->rgba = rgba;
    }
    light() { }
    ~light()
    {
      //delete rgba;
    }

    long mem_use() override
    {
      return identifier.size() +
      sizeof(power) +
      sizeof(size) +
      sizeof(me::vec4f);
    }

  };

  struct light_item : item {
    unsigned int light;
    light_item(std::string identifier, me::vec3d position, me::vec3d rotation, me::vec3d scale, me::vec3d origin, unsigned int light) :
    item(ME_ITEM_TYPE_LIGHT, identifier, position, rotation, scale, origin)
    {
      this->light = light;
    }
  };

};

#endif
