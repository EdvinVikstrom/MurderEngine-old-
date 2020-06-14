#ifndef XML_HELPER_H
  #define XML_HELPER_H

#include "../common.hpp"

namespace me_helper {
  
  inline std::string getXMLNodePath(rapidxml::xml_node<>* node)
  {
    std::string path = std::string(node->name()) + "/";
    rapidxml::xml_node<>* parent = node->parent();
    while(parent != 0)
    {
      path.append(std::string(parent->name()) + "/");
      parent = parent->parent();
    }
    return path;
  }
  
};

#endif
