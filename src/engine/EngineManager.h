#ifndef MURDER_ENGINE_MATH
  #define MURDER_ENGINE_MATH

#include "scene/scene.h"

namespace me {

  me::image* getImage(std::string id);
  me::texture* getTexture(std::string id);
  me::uvMap* getUvMap(std::string id);
  me::material* getMaterial(std::string id);
  me::mesh* getMesh(std::string id);
  me::shader* getShader(std::string id);

  void registerImage(std::string id, me::image* image);
  void registerTexture(std::string id, me::texture* texture);
  void registerUvMap(std::string id, me::uvMap* uvMap);
  void registerMaterial(std::string id, me::material* material);
  void registerMesh(std::string id, me::mesh* mesh);
  void registerShader(std::string id, me::shader* shader);

};

#endif
