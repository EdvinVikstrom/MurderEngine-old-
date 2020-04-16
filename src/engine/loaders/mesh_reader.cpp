#include <GL/glew.h>
#include "mesh_reader.h"

#include <iostream> // remove

extern std::string RENDERER_API_NAME;

static void process(me::mesh* mesh, std::vector<me::vertex> &vertices)
{
  mesh->vertices.reserve((mesh->indices.size() / mesh->offset) * sizeof(me::vertex));
  bool has_color = mesh->colors.size() != 0;
  me::vec4 def_color(1.0F, 1.0F, 1.0F, 1.0F);
  for (unsigned int i = 0; i < mesh->indices.size(); i+=mesh->offset)
  {
    uint32_t position_index = mesh->indices.at(i);
    uint32_t normal_index = mesh->indices.at(i+1);
    uint32_t texCoord_index = mesh->indices.at(i+2);
    uint32_t color_index = (has_color ? mesh->indices.at(i+3) : 0);

    me::vec3 &position = mesh->positions.at(position_index);
    me::vec3 &normal = mesh->normals.at(normal_index);
    me::vec2 &texCoord = mesh->texCoords.at(texCoord_index);
    me::vec4 &color = (has_color ? mesh->colors.at(color_index) : def_color);

    /* position */
    vertices.emplace_back(me::vertex(position, normal, texCoord, color));
  }
}

static bool find_vertex(std::vector<me::vertex> &vertices, me::vertex &vertex, uint32_t &index)
{
  for (uint32_t i = 0; i < vertices.size(); i++)
  {
    if (vertices.at(i)==vertex)
    {
      index = i;
      return true;
    }
  }
  return false;
}

void me::fformat::load_mesh(me::mesh* mesh, int usage)
{
  std::vector<me::vertex> raw_vertices;
  process(mesh, raw_vertices);
  uint32_t old_count = mesh->indices.size();
  mesh->indices.clear();
  mesh->indices.reserve(old_count / mesh->offset);
  uint32_t i = 0;
  for (me::vertex &vertex : raw_vertices)
  {
    uint32_t index = 0;
    if (find_vertex(mesh->vertices, vertex, index))
    {
      mesh->indices.emplace_back(index);
      continue;
    }
    mesh->indices.emplace_back(i);
    mesh->vertices.emplace_back(vertex);
    i++;
  }
}
