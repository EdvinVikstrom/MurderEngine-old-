#ifndef MESH_H
  #define MESH_H

#include <vector>
#include "material.h"

namespace me {

  struct mesh {
    std::string identifier;
    unsigned int buffer, indexBuffer;
    std::vector<float> vertices;
    unsigned int indiceCount, positionCount, normalCount;
    unsigned int* indices;
    me::vec3f* positions;
    me::vec3f* normals;
    me::uvMap* uvMap; // default uvMap
    me::material* material;

    mesh()
    {

    }

    ~mesh()
    {

    }

  };

};

#endif
