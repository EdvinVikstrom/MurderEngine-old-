#ifndef ITEM_H
  #define ITEM_H

namespace me {

  struct item {
    std::string identifier;
    me::vec3d* position;
    me::vec3d* rotation;
    me::vec3d* scale;

    item(std::string identifier, me::vec3d* position, me::vec3d* rotation, me::vec3d* scale)
    {
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
