#ifndef GLSL_READER_H
  #define GLSL_READER_H

#include "../../../kernel/kernel.h"
#include "../../../renderer/shader_program.h"
#include <string>
#include <map>

namespace me {

  namespace glsl_reader {

    int read_shader_file(const char* filepath, me::shader_program* program);

  };

};

#endif
