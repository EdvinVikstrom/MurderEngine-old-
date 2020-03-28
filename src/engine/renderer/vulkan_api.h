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
  int vertex(float x, float y, float z);
  int renderStart(unsigned int type);
  int renderEnd();
  int bindMesh(me::mesh* mesh);
  int unbindMesh();
  int mesh(me::mesh* mesh);
  int bindImage(me::image* image);
  int unbindImage();
  int plane(double posX, double posY, double scaleX, double scaleY);
  int color(float red, float green, float blue, float alpha);

  int reset();
  int translate(double x, double y, double z, double w);
  int rotate(double x, double y, double z, double w);
  int scale(double x, double y, double z, double w);
  int modify(unsigned int p, float value);

  int terminate();

};

#endif
