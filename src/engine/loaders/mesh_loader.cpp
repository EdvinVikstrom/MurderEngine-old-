#include <GL/glew.h>
#include "../scene/scene.h"
#include "mesh_loader.h"
#include "parsers/collada_parser.h"
#include "../utilities/FileUtils.h"

extern std::string RENDERER_API_NAME;

void me::loadMesh(me::mesh* mesh, int usage)
{
  unsigned int indexBuffer;
  unsigned int buffer;

  if (RENDERER_API_NAME=="opengl todo:")
  {
    /*
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, mesh->positions.count * sizeof(float), mesh->positions.values, GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3, (void*)12);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2, (void*)24);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indiceCount * sizeof(unsigned int), mesh->indices, GL_STATIC_DRAW);

    mesh->buffer = buffer;
    mesh->indexBuffer = indexBuffer;
    */
  }else if (RENDERER_API_NAME=="vulkan")
  {

  }
}

void me::processMeshFaces(me::mesh* mesh, unsigned int* faces, unsigned int faceCount, int vertexOffset, int normalOffset, int texCoordOffset)
{
  /*
  mesh->indiceCount = faceCount;
  mesh->indices = faces;
  for (int i = 0; i < faceCount; i+=3)
  {
    mesh->vertices.push_back(mesh->positions[faces[i+vertexOffset]].x);
    mesh->vertices.push_back(mesh->positions[faces[i+vertexOffset]].y);
    mesh->vertices.push_back(mesh->positions[faces[i+vertexOffset]].z);
    mesh->vertices.push_back(mesh->normals[faces[i+normalOffset]].x);
    mesh->vertices.push_back(mesh->normals[faces[i+normalOffset]].y);
    mesh->vertices.push_back(mesh->normals[faces[i+normalOffset]].z);
    mesh->vertices.push_back(mesh->uvMap->texCoords[faces[i+texCoordOffset]].x);
    mesh->vertices.push_back(mesh->uvMap->texCoords[faces[i+texCoordOffset]].y);
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
