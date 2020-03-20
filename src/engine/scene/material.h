#ifndef MATERIAL_H
  #define MATERIAL_H

namespace me {

  struct material {

    std::string identifier;
    wcolor rgba, gloss, metallic, roughness, emission, ior;

    material(std::string identifier, wcolor rgba, wcolor gloss, wcolor metallic, wcolor roughness, wcolor emission, wcolor ior)
    {
      this->identifier = identifier;
      this->rgba = rgba;
      this->gloss = gloss;
      this->metallic = metallic;
      this->roughness = roughness;
      this->emission = emission;
      this->ior = ior;
    }

    ~material()
    {

    }

  };

};

#endif
