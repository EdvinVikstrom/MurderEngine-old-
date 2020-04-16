#ifndef LIGHT_H
  #define LIGHT_H

namespace me {

  struct light {

    std::string identifier;
    uint32_t lightId;

    double power;
    double size;
    me::vec3 rgba;
    me::maths::mat4 model_matrix;

    bool loaded = false;

    light(std::string identifier, double power, double size, me::vec3 rgba, me::maths::mat4 model_matrix)
    {
      this->identifier = identifier;
      this->power = power;
      this->size = size;
      this->rgba = rgba;
      this->model_matrix = model_matrix;
    }

    light() { }

    ~light()
    {
      //delete rgba;
    }

  };

};

#endif
