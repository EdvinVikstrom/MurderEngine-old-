#ifndef SHADER_PROGRAM_H
  #define SHADER_PROGRAM_H

#include <map>

namespace me {

  enum shader_type {
    NONE,
    VERTEX,
    TESSELLATION,
    GEOMETRY,
    RASTERIZATION,
    FRAGMENT,
    COLOR_BLENDING
  };

  struct shader_program {
    std::map<me::shader_type, std::string> shaders;
  };

};

#endif
