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
    /*                     | offset 4 -->  0 1 2 3  | 4 5 6 7  | 8 9 ...   */
    /* indices offset | example: indices { v,n,t,c, | v,n,t,c, | v,n,... } */
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
