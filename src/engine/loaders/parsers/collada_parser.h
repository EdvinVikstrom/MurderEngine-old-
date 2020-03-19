#ifndef COLLADA_READER_H
  #define COLLADA_READER_H

#include "../../../external/rapidxml.hpp"

namespace collada {

  void parse_mesh(rapidxml::xml_node<>* node, me::mesh* mesh);
  void parse_faces(rapidxml::xml_node<>* mesh_node, me::mesh* mesh);
  void parse_effects(rapidxml::xml_node<>* node, me::material* material);
  void parse_camera(rapidxml::xml_node<>* node, me::mesh* mesh);

  me::mesh* loadColladaFile(char* data, unsigned int size, unsigned int* meshCount);

};

#endif
