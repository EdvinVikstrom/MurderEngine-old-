#ifndef MATERIAL_H
  #define MATERIAL_H

#include "texture.h"
#include <vector>

namespace me {

  struct material {
    std::string identifier;
    std::string shader;
    wcolor diffuse, emission, ior;
    std::vector<me::texture*> surfaces;
    std::vector<me::texture*> samplers;

    material(std::string identifier, std::string shader, wcolor diffuse, wcolor emission, wcolor ior)
    {
      this->identifier = identifier;
      this->shader = shader;
      this->diffuse = diffuse;
      this->emission = emission;
      this->ior = ior;
    }

    ~material()
    {

    }

  };

};

#endif
