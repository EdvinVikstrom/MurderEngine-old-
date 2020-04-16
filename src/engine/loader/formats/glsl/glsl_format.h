#ifndef GLSL_READER_H
  #define GLSL_READER_H

#include "../../../kernel/kernel.h"
#include "../../../MurderEngine.h"
#include <string>
#include <map>

namespace me {

  namespace glsl_format {

    int read_shader_file(const char* filepath, MeShaderProgram* program);

  };

};

#endif
