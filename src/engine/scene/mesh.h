#ifndef MESH_H
  #define MESH_H

#include "../utilities/ArrayUtils.h"

namespace me {

  struct vertex {
    me::vec3f position;
    me::vec3f normal;
    me::vec2f texCoord;
  };

  struct mesh {
    std::string identifier;
    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;
    me::material material;

    mesh(std::string identifier, std::vector<vertex> vertices, std::vector<unsigned int> indices, me::material material)
    {
      this->identifier = identifier;
      this->vertices = vertices;
      this->indices = indices;
      this->material = material;
    }

    mesh() { }

    ~mesh()
    {
      vertices.clear();
      indices.clear();
    }

  };

  struct mesh_item : item {
    unsigned int mesh;
    mesh_item(std::string identifier, me::vec3d position, me::vec3d rotation, me::vec3d scale, unsigned int mesh) :
    item(ME_ITEM_TYPE_MESH, identifier, position, rotation, scale)
    {
      this->mesh = mesh;
    }
  };

};

#endif
