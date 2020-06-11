#ifndef NODE_H
  #define NODE_H

#include "../kernel/kernel.hpp"
#include <map>

namespace me {

  struct node {
    std::string identifier;
    /* k: var name, v: var value */
    std::map<std::string, std::string> variables;

  };

};

#endif