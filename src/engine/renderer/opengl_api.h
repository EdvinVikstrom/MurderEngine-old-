#ifndef OPENGL_API_H
  #define OPENGL_API_H

#include "renderer_api.h"

class opengl_api : public renderer_api {

public:

  int initializeApi();
  int viewport(me::camera* camera, int x, int y, unsigned int width, unsigned int height);
  int useProgram(unsigned int program);
  me::device_info getDeviceInfo();

  int push();
  int pop();
  int clear();
  int bindMesh(me::mesh* mesh);
  int mesh(me::mesh* mesh);
  int unbindMesh();
  int bindMaterial(me::material* material);
  int unbindMaterial();
  int bindTexture(me::wcolor* texture);
  int unbindTexture();

  int reset();
  int vec3(int location, float x, float y, float z);
  int matrix4(int location, float* matrix);
  int modify(unsigned int p, float value);

  int terminate();

};

#endif
