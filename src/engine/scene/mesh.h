#ifndef MESH_H
  #define MESH_H

#include "../utilities/ArrayUtils.h"

namespace me {

  struct mesh {
    std::string identifier;
    unsigned int buffer, indexBuffer;
    utils::array<float>* vertices;
    utils::array<unsigned int>* indices;
    utils::array<me::vec3f>* positions;
    utils::array<me::vec3f>* normals;
    me::uvMap* uvMap; // default uvMap
    me::material* material;

    mesh(std::string identifier, unsigned int buffer, unsigned int indexBuffer, utils::array<float>* vertices, utils::array<unsigned int>* indices,
    utils::array<me::vec3f>* positions, utils::array<me::vec3f>* normals, me::uvMap* uvMap, me::material* material)
    {
      this->identifier = identifier;
      this->buffer = buffer;
      this->indexBuffer = indexBuffer;
      this->vertices = vertices;
      this->indices = indices;
      this->positions = positions;
      this->normals = normals;
      this->uvMap = uvMap;
      this->material = material;
    }

    mesh() { }

    ~mesh()
    {

    }

  };

  struct mesh_item : item {
    me::mesh* mesh;
    mesh_item(std::string identifier, me::vec3d* position, me::vec3d* rotation, me::vec3d* scale, me::mesh* mesh) :
    item(identifier, position, rotation, scale)
    {
      this->mesh = mesh;
    }
  };

};

#endif
