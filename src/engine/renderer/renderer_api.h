#ifndef RENDERER_API
  #define RENDERER_API

#include "shader_program.h"

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

namespace me {

  struct device_info {
    std::string company;
    std::string model;
    std::string version;
    std::string sl_version;
  };

  struct frenderer {

    virtual int initializeApi(void *window, me::shader_program* program) = 0;
    virtual int useProgram(me::shader_program &program) = 0;

    virtual me::device_info getDeviceInfo() = 0;

    virtual int clearFrame() = 0;
    virtual int cleanup() = 0;

  };

};

#endif
