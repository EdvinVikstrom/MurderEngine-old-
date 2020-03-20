#ifndef MESH_LOADER_H
  #define MESH_LOADER_H

#define ME_MESH_USAGE_STATIC                   0x15
#define ME_MESH_USAGE_DYNAMIC                  0x16

#define ME_MESH_FORMAT_COLLADA                 0x71

namespace me {

  void loadMesh(me::mesh* mesh, int usage);
  void processMeshFaces(me::mesh* mesh, unsigned int* faces, unsigned int faceCount, int vertexOffset, int normalOffset, int texCoordOffset);
  std::vector<me::item*> loadMeshFromFile(const char* filepath, unsigned int& itemCount);

};

#endif
