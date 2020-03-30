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
    me::mat4x4f matrix;
    me::sim::instance* instance;
    std::vector<me::sim::simulation*> simulations;

    // other
    me::vec3d velocity;

    item(unsigned char type, std::string identifier, me::mat4x4f matrix)
    {
      this->type = type;
      this->identifier = identifier;
      this->matrix = matrix;

      velocity = me::vec3d(0, 0, 0);
      instance = new me::sim::instance(&matrix, &velocity, nullptr);
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
