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
    unsigned int VAO, VBO, EBO;
    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<me::vec3f> positions;
    std::vector<me::vec3f> normals;
    std::vector<me::vec2f> texCoords;
    me::material* material;

    mesh(std::string identifier, unsigned int VAO, unsigned int VBO, unsigned int EBO, std::vector<vertex> vertices,std::vector<unsigned int> indices,
    std::vector<me::vec3f> positions, std::vector<me::vec3f> normals, std::vector<me::vec2f> texCoords, me::material* material)
    {
      this->identifier = identifier;
      this->VAO = VAO;
      this->VBO = VBO;
      this->EBO = EBO;
      this->vertices = vertices;
      this->indices = indices;
      this->positions = positions;
      this->normals = normals;
      this->texCoords = texCoords;
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
    item(ME_ITEM_TYPE_MESH, identifier, position, rotation, scale)
    {
      this->mesh = mesh;
    }
  };

};

#endif
