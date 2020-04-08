#include <GL/glew.h>
#include "mesh_reader.h"

#include <iostream> // remove

extern std::string RENDERER_API_NAME;

static void attach_attrib_array(unsigned int buffer, unsigned int index, unsigned int size, unsigned int type, unsigned int stride, void* offset)
{
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glEnableVertexAttribArray(index);
  glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
}

static void attach_array_buffer(unsigned int buffer_id, unsigned int size, void* array, int usage)
{
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  glBufferData(GL_ARRAY_BUFFER, size, array, usage);
}

void me::fformat::load_mesh(me::mesh* mesh, int usage)
{
  if (RENDERER_API_NAME=="opengl")
  {
    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &mesh->positionsVBO);
    glGenBuffers(1, &mesh->normalsVBO);
    glGenBuffers(1, &mesh->texCoordsVBO);
    glGenBuffers(1, &mesh->EBO);
    glBindVertexArray(mesh->VAO);

    /* positions */
    attach_array_buffer(mesh->positionsVBO, mesh->positions.size() * sizeof(me::vec3f), &mesh->positions[0], GL_STATIC_DRAW);
    attach_array_buffer(mesh->normalsVBO, mesh->normals.size() * sizeof(me::vec3f), &mesh->normals[0], GL_STATIC_DRAW);
    attach_array_buffer(mesh->texCoordsVBO, mesh->texCoords.size() * sizeof(me::vec2f), &mesh->texCoords[0], GL_STATIC_DRAW);

    /* indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.at(0)->indices.size() * sizeof(unsigned int), &mesh->indices.at(0)->indices[0], GL_STATIC_DRAW); // TODO: support for more indices

    attach_attrib_array(mesh->positionsVBO, 0, 3, GL_FLOAT, 0, nullptr);
    attach_attrib_array(mesh->normalsVBO, 1, 3, GL_FLOAT, 0, nullptr);
    attach_attrib_array(mesh->texCoordsVBO, 2, 2, GL_FLOAT, 0, nullptr);

    glBindVertexArray(0);
  }else if (RENDERER_API_NAME=="vulkan")
  {

  }
}
