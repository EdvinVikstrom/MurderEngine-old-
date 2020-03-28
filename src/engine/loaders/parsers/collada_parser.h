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
    std::string type;
    std::string source, init_from;
  };

  struct effect {
    std::string identifier;
    std::map<std::string, param*> params;
    me::wcolor
    *emission,
    *ambient,
    *diffuse,
    *specular,
    *shininess,
    *reflective,
    *reflectivity,
    *transparent,
    *transparency,
    *index_of_refraction;
    effect()
    {
      emission = new me::wcolor;
      ambient = new me::wcolor;
      diffuse = new me::wcolor;
      specular = new me::wcolor;
      shininess = new me::wcolor;
      reflective = new me::wcolor;
      reflectivity = new me::wcolor;
      transparent = new me::wcolor;
      transparency = new me::wcolor;
      index_of_refraction = new me::wcolor;
    }
    ~effect()
    {
      delete emission;
      delete ambient;
      delete diffuse;
      delete specular;
      delete shininess;
      delete reflective;
      delete reflectivity;
      delete transparent;
      delete transparency;
      delete index_of_refraction;
    }
  };

  bool parse_mesh(rapidxml::xml_node<>* mesh_node, me::mesh* mesh);
  bool parse_faces(rapidxml::xml_node<>* mesh_node, me::mesh* mesh);
  bool parse_effect(rapidxml::xml_node<>* effect_node, std::map<std::string, unsigned int> images, collada::effect* effect);
  bool parse_camera(rapidxml::xml_node<>* camera_node, me::camera* camera);
  bool parse_light(rapidxml::xml_node<>* light_node, me::light* light);
  bool parse_scene(rapidxml::xml_node<>* scene_node, std::map<std::string, unsigned int> &cameras, std::map<std::string, unsigned int> &lights, std::map<std::string, unsigned int> &images, std::map<std::string, collada::effect*> &effects, std::map<std::string, unsigned int> &materials, std::map<std::string, unsigned int> &meshes, std::vector<me::item*> &items);

  std::vector<me::item*> loadColladaFile(char* data, unsigned int size, unsigned int& itemCount);

};

#endif
