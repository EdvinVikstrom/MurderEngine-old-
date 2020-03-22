#ifndef COLLADA_READER_H
  #define COLLADA_READER_H

#include "../../../external/rapidxml.hpp"
#include "../../scene/scene.h"

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
    std::vector<collada::node_tree*> nodes;
  };

  struct effect {
    std::string identifier;
    std::string surface;
    me::wcolor *emission, *diffuse, *reflectivity, *transparent, *index_of_refraction;
  };

  bool parse_mesh(rapidxml::xml_node<>* mesh_node, me::mesh* mesh);
  bool parse_faces(rapidxml::xml_node<>* mesh_node, me::mesh* mesh);
  bool parse_effect(rapidxml::xml_node<>* effect_node, collada::effect* effect);
  bool parse_camera(rapidxml::xml_node<>* camera_node, me::camera* camera);
  bool parse_light(rapidxml::xml_node<>* light_node, me::light* light);
  bool parse_scene(rapidxml::xml_node<>* scene_node, std::map<std::string, me::camera*> &cameras, std::map<std::string, me::light*> &lights, std::map<std::string, me::image*> &images, std::map<std::string, collada::effect*> &effects, std::map<std::string, me::material*> &materials, std::map<std::string, me::mesh*> &meshes, std::vector<me::item*> &items);

  std::vector<me::item*> loadColladaFile(char* data, unsigned int size, unsigned int& itemCount);

};

#endif
