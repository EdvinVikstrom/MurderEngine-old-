#ifndef COLLADA_READER_H
  #define COLLADA_READER_H

#include <string>
#include "../../../external/rapidxml.hpp"
#include "../../scene/texture.h"

namespace collada {

  struct node_tree {
    std::string identifier;
    std::string value;
    std::vector<node_tree*> nodes;

    node_tree(std::string identifier, std::string value)
    {
      this->identifier = identifier;
      this->value = value;
    }

  };

  struct param {
    std::string sid;
    std::vector<me::node*> node;
  };

  struct effect {
    std::string identifier;
    std::vector<param> params;
    me::wcolor emission, diffuse, reflectivity, transparent, index_of_refraction;
  };

  void parse_mesh(rapidxml::xml_node<>* mesh_node, me::mesh* mesh);
  void parse_faces(rapidxml::xml_node<>* mesh_node, me::mesh* mesh);
  void parse_effect(rapidxml::xml_node<>* effect_node, me::effect* effect);
  void parse_camera(rapidxml::xml_node<>* camera_node, me::camera* camera);
  void parse_light(rapidxml::xml_node<>* light_node, me::light* light);

  me::scene_content* collada::loadColladaFile(char* data, unsigned int size, unsigned int& itemCount);

};

#endif
