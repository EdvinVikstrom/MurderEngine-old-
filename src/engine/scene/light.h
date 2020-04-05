#ifndef LIGHT_H
  #define LIGHT_H

namespace me {

  struct light {
    std::string identifier;
    double power;
    double size;
    me::vec4f rgba;
    me::transform transform;
    light(std::string identifier, double power, double size, me::vec4f rgba, me::transform &transform)
    {
      this->identifier = identifier;
      this->power = power;
      this->size = size;
      this->rgba = rgba;
      this->transform = transform;
    }
    light() { }
    ~light()
    {
      //delete rgba;
    }

  };

};

#endif
