#include <GL/glew.h>
#include "mesh_reader.h"

extern std::string RENDERER_API_NAME;

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
    glBindBuffer(GL_ARRAY_BUFFER, mesh->positionsVBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->positions->count * sizeof(me::vec3f), mesh->positions->values, GL_STATIC_DRAW);

    /* normals */
    glBindBuffer(GL_ARRAY_BUFFER, mesh->normalsVBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->normals->count * sizeof(me::vec3f), mesh->normals->values, GL_STATIC_DRAW);

    /* texCoords */
    glBindBuffer(GL_ARRAY_BUFFER, mesh->texCoordsVBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->texCoords->count * sizeof(me::vec2f), mesh->texCoords->values, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices->count * sizeof(unsigned int), mesh->indices->values, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->positionsVBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->normalsVBO);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->texCoordsVBO);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 24, (void*)0);

    glBindVertexArray(0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

  }else if (RENDERER_API_NAME=="vulkan")
  {

  }
}
