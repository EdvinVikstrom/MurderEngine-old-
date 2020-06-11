#ifndef SHADER_LOADER_HPP
  #define SHADER_LOADER_HPP

namespace me {

  void loadShadersProperties(me::bytebuff &buffer, me::MeShaders &shaders);
  void loadShaders(const std::string &directory, me::MeShaders &shaders, MeRenderer &renderer);
  MeShader loadShaderData(uint8_t* data, uint32_t length, uint8_t type, MeRenderer &renderer);
  MeShader readShaderFile(const std::string &filepath, MeRenderer &renderer);
  void loadShaderProgram(const std::string &filepath, uint8_t* types, MeShaderProgram &program, MeRenderer &renderer);

};

#endif
