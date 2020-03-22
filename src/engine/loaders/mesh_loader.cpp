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
    glGenBuffers(1, &mesh->VBO);
    glGenBuffers(1, &mesh->EBO);

    glBindVertexArray(mesh->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);

    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(me::vertex), &mesh->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(unsigned int), &mesh->indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(me::vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(me::vertex), (void*)12);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(me::vertex), (void*)24);

    glBindVertexArray(0);
  }else if (RENDERER_API_NAME=="vulkan")
  {

  }
}

void me::processMeshFaces(me::mesh* mesh, unsigned int* faces, unsigned int faceCount, int vertexOffset, int normalOffset, int texCoordOffset)
{
  for (int i = 0; i < faceCount; i+=3)
  {
    mesh->indices.push_back(i/3);

    float posX = mesh->positions[faces[i+vertexOffset]].x;
    float posY = mesh->positions[faces[i+vertexOffset]].y;
    float posZ = mesh->positions[faces[i+vertexOffset]].z;
    float normalX = mesh->normals[faces[i+normalOffset]].x;
    float normalY = mesh->normals[faces[i+normalOffset]].y;
    float normalZ = mesh->normals[faces[i+normalOffset]].z;
    float texCoordX = mesh->texCoords[faces[i+texCoordOffset]].x;
    float texCoordY = mesh->texCoords[faces[i+texCoordOffset]].y;
    mesh->vertices.push_back(
      { { posX, posY, posZ },
      { normalX, normalY, normalZ },
      { texCoordX, texCoordY } });
  }
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
