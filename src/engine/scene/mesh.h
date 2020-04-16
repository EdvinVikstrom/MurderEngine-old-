#ifndef MESH_H
  #define MESH_H

#include "../kernel/array_utils.h"

namespace me {

  enum Polygon {
    POINT,
    LINE,
    TRIANGLE,
    QUAD,
  };

  struct float_array {
    std::string identifier;
    unsigned int stride;
    std::vector<float> floats;

    inline void to_vec2(std::vector<me::vec2> &array)
    {
      array.reserve(floats.size() / 2);
      for (unsigned int i = 0; i < floats.size(); i+=2)
        array.emplace_back(me::vec2(floats.at(i), floats.at(i+1)));
    }
    inline void to_vec3(std::vector<me::vec3> &array)
    {
      array.reserve(floats.size() / 3);
      for (unsigned int i = 0; i < floats.size(); i+=3)
        array.emplace_back(me::vec3(floats.at(i), floats.at(i+1), floats.at(i+2)));
    }
    inline void to_vec4(std::vector<me::vec4> &array)
    {
      array.reserve(floats.size() / 4);
      for (unsigned int i = 0; i < floats.size(); i+=4)
        array.emplace_back(me::vec4(floats.at(i), floats.at(i+1), floats.at(i+2), floats.at(i+3)));
    }

  };

  struct vertex {
    me::vec3 position;
    me::vec3 normal;
    me::vec2 texCoord;
    me::vec4 color;

    vertex(me::vec3 position, me::vec3 normal, me::vec2 texCoord, me::vec4 color)
    {
      this->position = position;
      this->normal = normal;
      this->texCoord = texCoord;
      this->color = color;
    }

    vertex() { }

    inline bool operator==(vertex &v)
    {
      return position==v.position && normal==v.normal && texCoord==v.texCoord && color==v.color;
    }
  };

  struct mesh {

    std::string identifier;
    unsigned int meshId;
    unsigned int buffer;

    Polygon mode;

    std::vector<me::vec3> positions;
    std::vector<me::vec3> normals;
    std::vector<me::vec2> texCoords;
    std::vector<me::vec4> colors;

    std::vector<me::vertex> vertices;
    std::vector<uint32_t> indices;

    std::vector<me::material*> materials;
    me::maths::mat4 model_matrix;
    unsigned int offset = 0;

    bool loaded = false;

    mesh()
    {
    }

    ~mesh()
    {
    }

  };

};

#endif
