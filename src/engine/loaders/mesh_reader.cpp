#include <GL/glew.h>
#include "mesh_reader.h"

#include <iostream> // remove

extern std::string RENDERER_API_NAME;

void me::fformat::load_mesh(me::mesh* mesh, int usage)
{
  me::index_array* index_array = mesh->indices.at(0);
  if (RENDERER_API_NAME=="opengl")
  {
  }else if (RENDERER_API_NAME=="vulkan")
  {

  }
}
