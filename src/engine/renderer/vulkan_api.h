#ifndef ME_VULKAN_API_H
  #define ME_VULKAN_API_H

#include "renderer_api.h"
#include "../../external/vulkan/x86_64/include/vulkan/vulkan.hpp"

class vulkan_api : public renderer_api {

private:

  VkInstance instance;

public:

  void createInstance();

  int initializeApi();
  int viewport(me::camera* camera, int x, int y, unsigned int width, unsigned int height);
  int useProgram(unsigned int program);

  int push();
  int pop();
  int clear();
  int bindMesh(me::mesh* mesh);
  int mesh(me::mesh* mesh);
  int unbindMesh();
  int material(me::material* material);

  int reset();
  int transform(me::transform &transform);
  int modify(unsigned int p, float value);

  int terminate();

};

#endif
