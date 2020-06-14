#ifndef MESH_H
  #define MESH_H

#include "../kernel/array_utils.hpp"
#include "../math/transform.hpp"

namespace me {
  
  enum MeshPolygonMode : unsigned char {
    MESH_PLY_POINT,
    MESH_PLY_LINE,
    MESH_PLY_TRIANGLE,
    MESH_PLY_QUAD
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
  
  struct MeshInfo {
    uint32_t data[4];
    std::string source;
    std::string identifier;
    me::metadata* metadata = new me::metadata;
    MeshPolygonMode polygonMode;
  };
  
  struct Mesh {
    
    me::transform transform;
    
    std::vector<me::vec3> positions;
    std::vector<me::vec3> normals;
    std::vector<me::vec2> texCoords;
    std::vector<me::vec4> colors;
    
    std::vector<me::vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<me::Material*> materials;
    uint8_t offset;
    
    MeshInfo info;
    
    Mesh(me::transform transform, std::vector<me::vec3> positions, std::vector<me::vec3> normals, std::vector<me::vec2> texCoords, std::vector<me::vec4> colors, std::vector<me::vertex> vertices, std::vector<uint32_t> indices, std::vector<me::Material*> materials, uint8_t offset, MeshInfo info)
    {
      this->transform = transform;
      this->positions = positions;
      this->normals = normals;
      this->texCoords = texCoords;
      this->colors = colors;
      this->vertices = vertices;
      this->indices = indices;
      this->materials = materials;
      this->offset = offset;
      this->info = info;
    }
    
    Mesh(me::transform transform, MeshInfo info)
    {
      this->transform = transform;
      this->info = info;
    }
    
    Mesh()
    {
    }
    
    ~Mesh()
    {
    }
    
  };
  
};

#endif
