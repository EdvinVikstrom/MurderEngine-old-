#ifndef MATERIAL_H
  #define MATERIAL_H

namespace me {

  struct material {

    std::string identifier;
    me::wcolor *diffuse, *specular, *emission, *gloss, *ior;

    material(std::string identifier, me::wcolor* diffuse, me::wcolor* specular, me::wcolor* emission, me::wcolor* gloss, me::wcolor* ior)
    {
      this->identifier = identifier;
      this->diffuse = diffuse;
      this->specular = specular;
      this->emission = emission;
      this->gloss = gloss;
      this->ior = ior;
    }

    material()
    {
      diffuse = new me::wcolor(vec4(1.0F, 1.0F, 1.0F, 1.0F));
      specular = new me::wcolor(0.5F);
      emission = new me::wcolor(vec4(0.0F, 0.0F, 0.0F, 1.0F));
      ior = new me::wcolor(1.45F);
    }

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

  };

};

#endif
