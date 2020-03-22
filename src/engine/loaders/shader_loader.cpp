#include "shader_loader.h"
#include <GL/glew.h>
#include "../utilities/FileUtils.h"
#include "../utilities/Logger.h"

extern std::string RENDERER_API_NAME;

me::log* SHADER_LOGGER = new me::log("ShaderLoader", "\e[33m[%N] %T #%M \e[0m");

void loader::loadShader(const char* filepath, unsigned int& shader, unsigned int type)
{
  unsigned int size;
  char* data = file_utils_read(filepath, size);
  if (RENDERER_API_NAME=="opengl")
  {
    int numAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttributes);
    SHADER_LOGGER->out(std::string("Max attributes supported: ") + std::to_string(numAttributes) + "\n");
    unsigned int shaderType;
    if (type==ME_SHADER_TYPE_VERTEX) shaderType = GL_VERTEX_SHADER;
    if (type==ME_SHADER_TYPE_FRAGMENT) shaderType = GL_FRAGMENT_SHADER;
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &data, ((const int*)&size)); // wtf can i have a negative size!?
    glCompileShader(shader);
  }
}

void loader::linkShaders(unsigned int& program, unsigned int* shaders, unsigned int shaderCount)
{
  program = glCreateProgram();
  for (unsigned int i = 0; i < shaderCount; i++)
    glAttachShader(program, shaders[i]);
  glLinkProgram(program);
}
