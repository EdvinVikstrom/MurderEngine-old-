#ifndef OPENGL_API_H
  #define OPENGL_API_H

#include "../../MurderEngine.h"

namespace me {

  struct opengl_api : MeRenderer {

    MeShaderProgram* program;

    me::Mesh* meshBuffer[MESH_BUFF_CAP] = {nullptr};

    int initializeApi(MeInstance* instance);

    int loadMesh(me::Mesh* mesh);
    int loadImage(me::Image* image);

    int uniformMatrix4(int location, me::maths::mat4 matrix);
    int uniformVec2(int location, me::vec2 vec);
    int uniformVec3(int location, me::vec3 vec);
    int uniformVec4(int location, me::vec4 vec);

    int pushMesh(me::Mesh* mesh);
    int pullMesh(me::Mesh* mesh);

    int renderFrame(MeInstance* instance, unsigned long current_frame, bool &framebuffer_resized);
    int cleanup();

  };

};

#endif
