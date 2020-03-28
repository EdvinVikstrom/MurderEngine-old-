#ifndef ITEM_H
  #define ITEM_H

#define ME_ITEM_TYPE_MESH          45
#define ME_ITEM_TYPE_LIGHT         46
#define ME_ITEM_TYPE_CAMERA        47
#define ME_ITEM_TYPE_IMAGE         48

namespace me {

  struct item {
    unsigned char type;
    std::string identifier;
    me::vec3d position;
    me::vec3d rotation;
    me::vec3d scale;
    me::vec3d origin;

    item(unsigned char type, std::string identifier, me::vec3d position, me::vec3d rotation, me::vec3d scale, me::vec3d origin)
    {
      this->type = type;
      this->identifier = identifier;
      this->position = position;
      this->rotation = rotation;
      this->scale = scale;
      this->origin = origin;
    }

    item() { }

    ~item() { }

  };
};

#endif
