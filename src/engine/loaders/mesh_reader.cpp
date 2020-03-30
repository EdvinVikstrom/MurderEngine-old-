#include <GL/glew.h>
#include "../scene/scene.h"
#include "mesh_loader.h"
#include "parsers/collada_parser.h"
#include "../utilities/FileUtils.h"

#include <iostream> // remove

extern std::string RENDERER_API_NAME;

void me::loadMesh(me::mesh* mesh, int usage)
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
    glBufferData(GL_ARRAY_BUFFER, mesh->positions.count * sizeof(me::vec3f), mesh->positions.values, GL_STATIC_DRAW);

    /* normals */
    glBindBuffer(GL_ARRAY_BUFFER, mesh->normalsVBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->normals.count * sizeof(me::vec3f), mesh->normals.values, GL_STATIC_DRAW);

    /* texCoords */
    glBindBuffer(GL_ARRAY_BUFFER, mesh->texCoordsVBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->texCoords.count * sizeof(me::vec2f), mesh->texCoords.values, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.count * sizeof(unsigned int), mesh->indices.values, GL_STATIC_DRAW);

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

void me::processMeshFaces(me::mesh* mesh, unsigned int* faces, unsigned int faceCount, int vertexOffset, int normalOffset, int texCoordOffset)
{
  mesh->indices.allocate_mem(faceCount);
  for (unsigned int i = 0; i < faceCount; i+=3)
    mesh->indices.values[i/3] = faces[i];
  /*
  unsigned int positionSize = mesh->positions.count * 3;
  unsigned int normalSize = mesh->normals.count * 3;
  unsigned int texCoordSize = mesh->texCoords.count * 2;
  mesh->vertices.allocate_mem(positionSize+normalSize+texCoordSize);
  mesh->vertices.put(0, mesh->positions.values, mesh->positions.count);
  mesh->vertices.put(positionSize, mesh->normals.values, mesh->normals.count);
  mesh->vertices.put(positionSize+normalSize, mesh->texCoords.values, mesh->texCoords.count);
  mesh->indices.allocate_mem(faceCount);
  for (unsigned int i = 0; i < faceCount; i++)
  {
    unsigned int offset = 0;
    if (i % 3 == 1) offset = positionSize;
    else if (i % 3 == 2) offset = positionSize + normalSize;
    mesh->indices.values[i] = (faces[i]+offset);
  }
  */
}

std::vector<me::item*> me::loadMeshFromFile(const char* filepath, unsigned int& itemCount)
{
  unsigned int size;
  char* data = file_utils_read(filepath, size);
  unsigned int format = ME_MESH_FORMAT_COLLADA;
  if (format==ME_MESH_FORMAT_COLLADA)
    return collada::loadColladaFile(data, size, itemCount);
  return {};
}
