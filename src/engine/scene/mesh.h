#ifndef MESH_H
  #define MESH_H

#include "../utilities/ArrayUtils.h"

namespace me {

  struct mesh {
    std::string identifier;
    unsigned int VAO, positionsVBO, normalsVBO, texCoordsVBO, EBO;
    me::array<me::vec3f> positions;
    me::array<me::vec3f> normals;
    me::array<me::vec2f> texCoords;
    me::array<float> vertices;
    me::array<unsigned int> indices;
    unsigned int material;

    mesh(std::string identifier, unsigned int VAO, unsigned int positionsVBO, unsigned int normalsVBO, unsigned int texCoordsVBO, unsigned int EBO, unsigned int material)
    {
      this->identifier = identifier;
      this->VAO = VAO;
      this->positionsVBO = positionsVBO;
      this->normalsVBO = normalsVBO;
      this->texCoordsVBO = texCoordsVBO;
      this->EBO = EBO;
      this->material = material;
    }

    mesh() { }

    ~mesh()
    {
      positions.unallocate_mem();
      normals.unallocate_mem();
      texCoords.unallocate_mem();
      indices.unallocate_mem();
    }

  };

  struct mesh_item : item {
    unsigned int mesh;
    mesh_item(std::string identifier, me::vec3d position, me::vec3d rotation, me::vec3d scale, me::vec3d origin, unsigned int mesh) :
    item(ME_ITEM_TYPE_MESH, identifier, position, rotation, scale, origin)
    {
      this->mesh = mesh;
    }
  };

};

#endif
