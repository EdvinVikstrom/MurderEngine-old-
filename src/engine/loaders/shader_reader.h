#ifndef SHADER_LOADER_H
  #define SHADER_LOADER_H

#define ME_SHADER_TYPE_VERTEX             54
#define ME_SHADER_TYPE_FRAGMENT           87

#include "../scene/scene.h"

namespace loader {

  int loadShaders(const std::string &filepath, unsigned int* shaders, unsigned int shaderCount);
  int linkShaders(unsigned int& program, unsigned int* shaders, unsigned int shaderCount);

};

#endif
