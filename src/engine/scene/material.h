#ifndef MATERIAL_H
  #define MATERIAL_H

namespace me {

  struct material {

    std::string identifier;
    me::wcolor *rgba, *gloss, *metallic, *roughness, *emission, *ior;

    material(std::string identifier, me::wcolor* rgba, me::wcolor* gloss, me::wcolor* metallic, me::wcolor* roughness, me::wcolor* emission, me::wcolor* ior)
    {
      this->identifier = identifier;
      this->rgba = rgba;
      this->gloss = gloss;
      this->metallic = metallic;
      this->roughness = roughness;
      this->emission = emission;
      this->ior = ior;
    }

    material() { }

    ~material()
    {
      delete rgba;
      delete gloss;
      delete metallic;
      delete roughness;
      delete emission;
      delete ior;
    }

  };

};

#endif
