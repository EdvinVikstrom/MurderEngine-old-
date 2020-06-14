#ifndef SHADER_LOADER_HPP
  #define SHADER_LOADER_HPP

#include "../kernel/io/filebuff.hpp"
#include "../MurderEngine.hpp"

namespace me {

  void loadShaders(const std::string &directory, MeShaders &shaders, MeRenderer &renderer);
  void loadShadersProperties(me::bytebuff &buffer, MeShaders &shaders);
  MeShader loadShaderData(uint8_t* data, uint32_t length, uint8_t type, MeRenderer &renderer);
  MeShader readShaderFile(const std::string &filepath, MeRenderer &renderer);
  void loadShaderProgram(const std::string &filepath, uint8_t* types, uint8_t count, MeShaderProgram &program, MeRenderer &renderer);

};

#endif
