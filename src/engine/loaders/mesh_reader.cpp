#include <GL/glew.h>
#include "mesh_reader.h"

#include <iostream> // remove

extern std::string RENDERER_API_NAME;

static void attach_attrib_array(unsigned int buffer, unsigned int index, unsigned int size, unsigned int type, unsigned int stride)
{
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glEnableVertexAttribArray(index);
  glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)0);
}

void me::fformat::load_mesh(me::mesh* mesh, int usage)
{
  if (RENDERER_API_NAME=="opengl")
  {
    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &mesh->positionsVBO);
    glGenBuffers(1, &mesh->normalsVBO);
    glGenBuffers(1, &mesh->texCoordsVBO);
    glGenBuffers(1, &mesh->materialsVBO);
    glGenBuffers(1, &mesh->EBO);

    glBindVertexArray(mesh->VAO);

    /* positions */
    glBindBuffer(GL_ARRAY_BUFFER, mesh->positionsVBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->positions->count * sizeof(me::vec3f), mesh->positions->values, GL_STATIC_DRAW);
    /* normals */
    glBindBuffer(GL_ARRAY_BUFFER, mesh->normalsVBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->normals->count * sizeof(me::vec3f), mesh->normals->values, GL_STATIC_DRAW);
    /* texCoords */
    glBindBuffer(GL_ARRAY_BUFFER, mesh->texCoordsVBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->texCoords->count * sizeof(me::vec2f), mesh->texCoords->values, GL_STATIC_DRAW);
    /* indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices->count * sizeof(unsigned int), mesh->indices->values, GL_STATIC_DRAW);

    if (mesh->positions->count > 0) attach_attrib_array(mesh->positionsVBO, 0, 3, GL_FLOAT, 0);
    if (mesh->normals->count > 0) attach_attrib_array(mesh->normalsVBO, 1, 3, GL_FLOAT, 12);
    if (mesh->texCoords->count > 0) attach_attrib_array(mesh->texCoordsVBO, 2, 2, GL_FLOAT, 24);
    //if (mesh->materials != nullptr && mesh->materials->size() > 1) attach_attrib_array(mesh->materialsVBO, 0, 2, GL_FLOAT, 32); /* if it is only one material, the "faces" only have one choice */

    glBindVertexArray(0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    //glDisableVertexAttribArray(3);

  }else if (RENDERER_API_NAME=="vulkan")
  {

  }
}
