#ifndef MURDER_ENGINE_MATH
  #define MURDER_ENGINE_MATH

#include "scene/scene.h"

namespace me {

  me::image* getImage(unsigned int id);
  me::material* getMaterial(unsigned int id);
  me::mesh* getMesh(unsigned int id);
  me::camera* getCamera(unsigned int id);
  me::light* getLight(unsigned int id);

  unsigned int getImageLink(std::string identifier);
  unsigned int getMaterialLink(std::string identifier);
  unsigned int getMeshLink(std::string identifier);
  unsigned int getCameraLink(std::string identifier);
  unsigned int getLightLink(std::string identifier);

  unsigned int registerImage(me::image* image);
  unsigned int registerMaterial(me::material* material);
  unsigned int registerMesh(me::mesh* mesh);
  unsigned int registerCamera(me::camera* camera);
  unsigned int registerLight(me::light* light);

  void init();
  void cleanup();

};

#endif
