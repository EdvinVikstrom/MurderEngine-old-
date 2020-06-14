#ifndef OPENGL_API_HPP
  #define OPENGL_API_HPP

#include "../../MurderEngine.hpp"

namespace me {

  struct opengl_api : MeRenderer {

    int initializeApi(MeInstance* instance);
    int compileShader(const std::string &source, uint8_t type, MeShader &shader);
    int makeShaderProgram(MeShader* shaders, uint8_t count, MeShaderProgram &program);

    int uniform1f(int location, float* f, uint32_t count = 1);
    int uniform2f(int location, me::vec2* vec, uint32_t count = 1);
    int uniform3f(int location, me::vec3* vec, uint32_t count = 1);
    int uniform4f(int location, me::vec4* vec, uint32_t count = 1);

    int uniform1i(int location, int* i, uint32_t count = 1);
    int uniform2i(int location, me::vec2i* vec, uint32_t count = 1);
    int uniform3i(int location, me::vec3i* vec, uint32_t count = 1);
    int uniform4i(int location, me::vec4i* vec, uint32_t count = 1);

    int uniform1ui(int location, uint32_t* i, uint32_t count = 1);
    int uniform2ui(int location, me::vec2ui* vec, uint32_t count = 1);
    int uniform3ui(int location, me::vec3ui* vec, uint32_t count = 1);
    int uniform4ui(int location, me::vec4ui* vec, uint32_t count = 1);

    int uniformMat2x2(int location, real_t* mat, uint32_t count = 1);
    int uniformMat3x3(int location, real_t* mat, uint32_t count = 1);
    int uniformMat4x4(int location, real_t* mat, uint32_t count = 1);
    int uniformMat2x3(int location, real_t* mat, uint32_t count = 1);
    int uniformMat3x2(int location, real_t* mat, uint32_t count = 1);
    int uniformMat2x4(int location, real_t* mat, uint32_t count = 1);
    int uniformMat4x2(int location, real_t* mat, uint32_t count = 1);
    int uniformMat3x4(int location, real_t* mat, uint32_t count = 1);
    int uniformMat4x3(int location, real_t* mat, uint32_t count = 1);

    int pushMesh(me::Mesh* mesh);
    int pullMesh(me::Mesh* mesh);

    int pushImage(me::Image* image);
    int pullImage(me::Image* image);

    int renderFrame(MeInstance* instance, unsigned long current_frame, bool &framebuffer_resized);
    int cleanup();

  };

};

#endif
