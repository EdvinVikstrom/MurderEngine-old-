#ifndef LIGHT_H
  #define LIGHT_H

namespace me {

  struct Light {

    std::string identifier;

    double power;
    double size;
    me::vec3 rgba;
    me::maths::mat4 model_matrix;

    Light(std::string identifier, double power, double size, me::vec3 rgba, me::maths::mat4 model_matrix)
    {
      this->identifier = identifier;
      this->power = power;
      this->size = size;
      this->rgba = rgba;
      this->model_matrix = model_matrix;
    }

    Light() { }

    ~Light()
    {
      //delete rgba;
    }

  };

};

#endif
