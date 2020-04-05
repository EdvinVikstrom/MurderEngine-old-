#ifndef MESH_H
  #define MESH_H

#include "../kernel/array_utils.h"

namespace me {

  struct mesh {
    std::string identifier;
    unsigned int VAO, positionsVBO, normalsVBO, texCoordsVBO, materialsVBO, EBO;
    me::array<me::vec3f*>* positions;
    me::array<me::vec3f*>* normals;
    me::array<me::vec2f*>* texCoords;
    me::array<unsigned int*>* indices; /* if materials.size() > 1, use 1 extra index for material */
    std::vector<me::material*>* materials;

    mesh() { }

    ~mesh()
    {
    }

  };

};

#endif
