#ifndef SIMULATION_H
  #define SIMULATION_H

#include "../utilities/properties.h"

namespace me {

  struct simulation {
    std::string name;
    property_list* properties;
    simulation(std::string name, property_list* properties)
    {
      this->name = name;
      this->properties = properties;
    }
  };

};

#endif
