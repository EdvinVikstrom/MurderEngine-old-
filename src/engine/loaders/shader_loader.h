#ifndef SHADER_LOADER_H
  #define SHADER_LOADER_H

#include "../scene/scene.h"

namespace loader {

  void loadShader(const char* filepath, unsigned int& shader, unsigned int type);
  void linkShaders(unsigned int& program, unsigned int* shaders, unsigned int shaderCount);

};

#endif
