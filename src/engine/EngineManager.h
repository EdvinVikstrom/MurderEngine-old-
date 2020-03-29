#ifndef MURDER_ENGINE_MATH
  #define MURDER_ENGINE_MATH

#include "scene/scene.h"
#include "simulation/simulation.h"

namespace me {

  me::image* getImage(unsigned int id);
  me::material* getMaterial(unsigned int id);
  me::mesh* getMesh(unsigned int id);
  me::light* getLight(unsigned int id);
  me::camera* getCamera(unsigned int id);
  me::shader* getShader(unsigned int id);

  me::sim::simulation* getSimulation(unsigned int id);

  unsigned int registerImage(me::image* image);
  unsigned int registerMaterial(me::material* material);
  unsigned int registerMesh(me::mesh* mesh);
  unsigned int registerLight(me::light* light);
  unsigned int registerCamera(me::camera* camera);
  unsigned int registerShader(me::shader* shader);

  unsigned int registerSimulation(me::sim::simulation* simulation);

  void cleanup();

};

#endif
