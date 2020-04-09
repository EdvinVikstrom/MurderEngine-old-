#ifndef LIGHT_H
  #define LIGHT_H

namespace me {

  struct light {
    std::string identifier;
    double power;
    double size;
    me::vec4 rgba;
    light(std::string identifier, double power, double size, me::vec4 rgba)
    {
      this->identifier = identifier;
      this->power = power;
      this->size = size;
      this->rgba = rgba;
    }
    light() { }
    ~light()
    {
      //delete rgba;
    }

  };

};

#endif
