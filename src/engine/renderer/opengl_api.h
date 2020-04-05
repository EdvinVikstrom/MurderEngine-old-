#ifndef OPENGL_API_H
  #define OPENGL_API_H

#include "renderer_api.h"

class opengl_api : public renderer_api {

public:

  int initializeApi();
  int viewport(me::camera* camera, int x, int y, unsigned int width, unsigned int height);
  int useProgram(unsigned int program);

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

  int quad(double fx, double fy, double tx, double ty);

  int reset();
  int transform(me::transform &transform);
  int translate(double x, double y, double z);
  int rotate(double x, double y, double z);
  int scale(double x, double y, double z);
  int modify(unsigned int p, float value);

  int terminate();

};

#endif
