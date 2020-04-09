#ifndef MESH_H
  #define MESH_H

#include "../kernel/array_utils.h"

namespace me {

  struct float_array {
    std::string identifier;
    unsigned int stride;
    std::vector<float> floats;

    void to_vec2(std::vector<me::vec2> &array)
    {
      array.reserve(floats.size() / 2);
      for (unsigned int i = 0; i < floats.size(); i+=2)
        array.emplace_back(floats.at(i), floats.at(i+1));
    }

    void to_vec3(std::vector<me::vec3> &array)
    {
      array.reserve(floats.size() / 3);
      for (unsigned int i = 0; i < floats.size(); i+=3)
        array.emplace_back(floats.at(i), floats.at(i+1), floats.at(i+2));
    }

    void to_vec4(std::vector<me::vec4> &array)
    {
      array.reserve(floats.size() / 4);
      for (unsigned int i = 0; i < floats.size(); i+=4)
        array.emplace_back(floats.at(i), floats.at(i+1), floats.at(i+2), floats.at(i+3));
    }

  };

  struct index_array {
    std::vector<unsigned int> indices;
    me::material* material;
  };

  struct mesh {
    std::string identifier;
    unsigned int VAO, positionsVBO, normalsVBO, texCoordsVBO, materialsVBO, EBO;
    std::vector<me::vec3> positions;
    std::vector<me::vec3> normals;
    std::vector<me::vec2> texCoords;
    std::vector<me::vec4> colors;
    unsigned int offset = 0;
    std::vector<me::index_array*> indices;

    mesh()
    {
    }

    ~mesh()
    {
    }

  };

};

#endif
