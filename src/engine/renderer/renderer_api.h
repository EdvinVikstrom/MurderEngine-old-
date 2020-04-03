#ifndef RENDERER_API
  #define RENDERER_API

/* Render Shape Type Thing */
#define ME_TRIANGLES                 0
#define ME_QUADS                     1
#define ME_TRIANGLE_STRIP            2
#define ME_QUAD_STRIP                3
#define ME_POLYGONS                  4
#define ME_LINES                     5
#define ME_LINE_STRIP                6
#define ME_LINE_LOOP                 7
#define ME_POINTS                    8

/* Image Stuff */
#define ME_TEXTURE_2D                         9
#define ME_TEXTURE_3D                         10
#define ME_TEX_NEAREST                        11
#define ME_TEX_LINEAR                         12

#define ME_MATRIX_PROJECTION                  13
#define ME_MATRIX_MODELVIEW                   14

#define ME_CULL_FACE                          15
#define ME_BACK                               16
#define ME_FRONT                              17
#define ME_FRONT_AND_BACK                     18

#define ME_DEPTH_TEST                         19

/* Shader Stuff */
#define ME_SHADER_VERTEX                      234
#define ME_SHADER_FRAGMENT                    235

#include "../scene/scene.h"

class renderer_api {

public:

  virtual int initializeApi() = 0;
  virtual int viewport(me::camera* camera, int x, int y, unsigned int width, unsigned int height) = 0;
  virtual int useProgram(unsigned int program) = 0;

  virtual int push() = 0;
  virtual int pop() = 0;
  virtual int clear() = 0;
  virtual int bindMesh(me::mesh* mesh) = 0;
  virtual int mesh(me::mesh* mesh) = 0;
  virtual int unbindMesh() = 0;
  virtual int material(me::material* material) = 0;

  virtual int reset() = 0;
  virtual int transform(me::transform &transform) = 0;
  virtual int modify(unsigned int p, float value) = 0;

  virtual int terminate() = 0;

};

#endif
