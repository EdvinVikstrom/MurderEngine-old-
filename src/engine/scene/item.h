#ifndef ITEM_H
  #define ITEM_H

#define ME_ITEM_TYPE_MESH          45
#define ME_ITEM_TYPE_LIGHT         46
#define ME_ITEM_TYPE_CAMERA        47
#define ME_ITEM_TYPE_UI_ELEMENT    48

namespace me {

  struct item {
    unsigned char type;
    std::string identifier;
    me::vec3d position;
    me::vec3d rotation;
    me::vec3d scale;

    item(unsigned char type, std::string identifier, me::vec3d position, me::vec3d rotation, me::vec3d scale)
    {
      this->type = type;
      this->identifier = identifier;
      this->position = position;
      this->rotation = rotation;
      this->scale = scale;
    }

    item() { }

    ~item() { }

  };
};

#endif
