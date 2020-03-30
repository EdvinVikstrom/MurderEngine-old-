#ifndef MATERIAL_H
  #define MATERIAL_H

namespace me {

  struct material : mem_utils {

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
      /*
      delete rgba;
      delete gloss;
      delete metallic;
      delete roughness;
      delete emission;
      delete ior;
      */
    }

    long mem_use() override
    {
      return identifier.size() +
      (rgba != nullptr ? rgba->mem_use() : 0) +
      (gloss != nullptr ? gloss->mem_use() : 0) +
      (metallic != nullptr ? metallic->mem_use() : 0) +
      (roughness != nullptr ? roughness->mem_use() : 0) +
      (emission != nullptr ? emission->mem_use() : 0) +
      (ior != nullptr ? ior->mem_use() : 0);
    }

  };

};

#endif
