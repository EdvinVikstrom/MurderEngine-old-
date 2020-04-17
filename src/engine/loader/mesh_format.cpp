#include "mesh_format.h"

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

    /* getting the positions, normals... from the indices */
    me::vec3 &position = mesh->positions.at(position_index);
    me::vec3 &normal = mesh->normals.at(normal_index);
    me::vec2 &texCoord = mesh->texCoords.at(texCoord_index);
    me::vec4 &color = (has_color ? mesh->colors.at(color_index) : def_color);

    /* position */
    /* packing all the positions, normals, texCoords, colors in to a vertex */
    vertices.emplace_back(me::vertex(position, normal, texCoord, color));
  }
}

static bool find_vertex(std::vector<me::vertex> &vertices, me::vertex &vertex, uint32_t &index)
{
  // TODO: improve
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

// TODO: MeshFormat
void me::format::formatMesh(me::mesh* mesh, MeshFormat format)
{
  std::vector<me::vertex> raw_vertices;
  process(mesh, raw_vertices);

  /* store the old indices count so we can calculate new stuff */
  uint32_t old_count = mesh->indices.size();

  /* removing all indices so we can add the new ones */
  mesh->indices.clear();

  /* calculating the new size of indices and allocating */
  mesh->indices.reserve(old_count / mesh->offset);
  uint32_t i = 0;

  /* searching for duplicate vertices and filling in indices */
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
