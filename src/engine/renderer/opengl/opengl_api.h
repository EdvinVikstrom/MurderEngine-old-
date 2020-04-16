#ifndef OPENGL_API_H
  #define OPENGL_API_H

#include "../MurderEngine.h"

namespace me {

  struct opengl_api : MeRenderer {

    MeShaderProgram* program;

    int initializeApi(MeInstance* instance);

    int setupMeshRenderer(MeInstance* instance);
    int setupImageRenderer(MeInstance* instance);
    int loadMesh(me::mesh* mesh);
    int loadImage(me::image* image);

    int uniformMatrix4(int location, me::maths::mat4 matrix);
    int uniformVec2(int location, me::vec2 vec);
    int uniformVec3(int location, me::vec3 vec);
    int uniformVec4(int location, me::vec4 vec);

    int renderFrame(MeInstance* instance, unsigned long current_frame, bool &framebuffer_resized);
    int cleanup();

  };

};

#endif
