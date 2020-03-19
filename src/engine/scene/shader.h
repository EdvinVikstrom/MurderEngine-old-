#ifndef SHADER_H
  #define SHADER_H

#include <string>

namespace me {

  struct shader {
    std::string identifier;
    unsigned int programId;
    const char* source;
  };

};

#endif
