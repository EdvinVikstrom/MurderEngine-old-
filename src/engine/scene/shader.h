#ifndef SHADER_H
  #define SHADER_H

#define ME_SHADER_TYPE_VERTEX            15
#define ME_SHADER_TYPE_FRAGMENT          76

namespace me {

  struct shader {
    std::string identifier;
    unsigned int programId;
    const char* source;
  };

};

#endif
