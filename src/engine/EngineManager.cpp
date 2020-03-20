#include <map>

#include "EngineManager.h"

extern std::string RENDER_API;

namespace me {

  /* Texture/Material/Mesh/Shader logic */

  static std::map<std::string, me::image*> images;
  static std::map<std::string, me::texture*> textures;
  static std::map<std::string, me::uvMap*> uvMaps;
  static std::map<std::string, me::shader*> shaders;
  static std::map<std::string, me::material*> materials;
  static std::map<std::string, me::mesh*> meshes;

  me::image* getImage(std::string id)
  {
    return images[id];
  }
  me::texture* getTexture(std::string id)
  {
    return textures[id];
  }
  me::uvMap* getUvMap(std::string id)
  {
    return uvMaps[id];
  }
  me::material* getMaterial(std::string id)
  {
    return materials[id];
  }
  me::mesh* getMesh(std::string id)
  {
    return meshes[id];
  }
  me::shader* getShader(std::string id)
  {
    return shaders[id];
  }

  void registerImage(std::string id, me::image* image)
  {
    images[id] = image;
  }
  void registerTexture(std::string id, me::texture* texture)
  {
    textures[id] = texture;
  }
  void registerUvMap(std::string id, me::uvMap* uvMap)
  {
    uvMaps[id] = uvMap;
  }
  void registerMaterial(std::string id, me::material* material)
  {
    materials[id] = material;
  }
  void registerMesh(std::string id, me::mesh* mesh)
  {
    meshes[id] = mesh;
  }
  void registerShader(std::string id, me::shader* shader)
  {
    shaders[id] = shader;
  }

};
