#ifndef PROPERTIES_H
  #define PROPERTIES_H

#include <string>
#include <vector>
#include <map>
#include "../math/vectors.h"

namespace me {

  template<typename T>
  struct property {
    std::string identifier;
    T value;
    std::vector<T> validValues;

    property(std::string identifier, T value)
    {
      this->identifier = identifier;
      this->value = value;
    }

    ~property()
    {

    }

    virtual bool validValue(T value) = 0;
    virtual std::vector<T> getValidValues() = 0;
  };

  struct property_list {
    /* param[0]: the category | param[1]: the property */
    std::map<std::string, me::property<>*> properties;

    ~property_list()
    {
      properties.clear();
    }

  };

  struct float_property : property<float> {
    me::vec2f range;
    float_property(std::string identifier, float value, me::vec2f range) : property<float>(identifier, value)
    {
      this->range = range;
    }
    bool validValue(T value) override;
    std::vector<T> getValidValues() override; // i don't think so
  };

};

#endif
