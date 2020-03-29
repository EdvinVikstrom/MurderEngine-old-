#ifndef ITEM_H
  #define ITEM_H

#define ME_ITEM_TYPE_MESH          45
#define ME_ITEM_TYPE_LIGHT         46
#define ME_ITEM_TYPE_CAMERA        47
#define ME_ITEM_TYPE_IMAGE         48

#include "../simulation/simulation.h"

namespace me {

  struct item {
    unsigned char type;
    std::string identifier;
    me::vec3d position;
    me::vec3d rotation;
    me::vec3d scale;
    me::vec3d origin;
    me::sim::instance* instance;
    std::vector<me::sim::simulation*> simulations;

    item(unsigned char type, std::string identifier, me::vec3d position, me::vec3d rotation, me::vec3d scale, me::vec3d origin)
    {
      this->type = type;
      this->identifier = identifier;
      this->position = position;
      this->rotation = rotation;
      this->scale = scale;
      this->origin = origin;
      instance = new me::sim::instance(&position, &rotation, new me::vec3d(0, 0, 0), nullptr);
    }

    item() { }

    ~item()
    {
      delete instance;
      simulations.clear();
    }

    void update();

  };
};

#endif
