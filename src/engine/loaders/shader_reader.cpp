#include <GL/glew.h>
#include <string>
#include <vector>
#include "shader_loader.h"
#include "../MurderEngine.h"
#include "../utilities/FileUtils.h"
#include "../utilities/Logger.h"
#include "../utilities/StringUtils.h"

extern std::string RENDERER_API_NAME;

static me::log* SHADER_LOGGER = new me::log("ShaderLoader",
"\e[35m[%N] %T #%M \e[0m",
"\e[35m[%N] %T\e[0m \e[33m#%M \e[0m",
"\e[35m[%N] %T\e[0m \e[31m#%M \e[0m",
"\e[34m[%N] %T #%M \e[0m"
);

int loader::loadShaders(const std::string &filepath, unsigned int* shaders, unsigned int shaderCount)
{
  unsigned int size;
  char* data = file_utils_read(filepath, size);
  std::vector<std::string> lines = utils::lines(data);
  std::vector<std::pair<unsigned int, std::string>> sources;
  bool appending = false;
  for (std::string &line : lines)
  {
    if (line=="#vertex" || line=="#fragment")
    {
      unsigned int shaderType = -1;
      if (line=="#vertex") shaderType = ME_SHADER_TYPE_VERTEX;
      if (line=="#fragment") shaderType = ME_SHADER_TYPE_FRAGMENT;
      sources.push_back(std::make_pair(shaderType, ""));
      appending = true;
      continue;
    }else if (line=="#end")
    {
      appending = false;
      continue;
    }
    if (appending)
      sources.at(sources.size()-1).second.append(line + "\n");
  }
  delete[] data;
  if (RENDERER_API_NAME=="opengl")
  {
    int numAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttributes);
    SHADER_LOGGER->out(std::string("Max attributes supported: ") + std::to_string(numAttributes) + "\n");
    for (unsigned int i = 0; i < sources.size() && i < shaderCount; i++)
    {
      auto &source = sources.at(i);
      unsigned int shaderType = source.first;
      std::string &data = source.second;
      std::string shaderName;
      if (shaderType==ME_SHADER_TYPE_VERTEX)
      {
        shaderType = GL_VERTEX_SHADER;
        shaderName = "Vertex";
      }
      else if (shaderType==ME_SHADER_TYPE_FRAGMENT)
      {
        shaderType = GL_FRAGMENT_SHADER;
        shaderName = "Fragment";
      }
      shaders[i] = glCreateShader(shaderType);
      std::cout << "real id: " << shaders[i] << "\n";
      const char *str = data.c_str();
      SHADER_LOGGER->out("  % Compiling " + shaderName + " shader\n");
      glShaderSource(shaders[i], 1, &str, nullptr);
      glCompileShader(shaders[i]);

      int status;
      glGetShaderiv(shaders[i], GL_COMPILE_STATUS, &status);
      if (status != GL_TRUE)
      {
        unsigned int maxLength = 512;
        int infoLength;
        char info[maxLength];
        glGetShaderInfoLog(shaders[i], maxLength, &infoLength, info);
        std::string errorMsg(info, infoLength);
        SHADER_LOGGER->err(shaderName + " shader failed to compile: " + errorMsg + "\n");
        return ME_ERR;
      }
      SHADER_LOGGER->out(shaderName + " shader compiled\n");
    }
  }
  return ME_FINE;
}

int loader::linkShaders(unsigned int& program, unsigned int* shaders, unsigned int shaderCount)
{
  program = glCreateProgram();
  for (unsigned int i = 0; i < shaderCount; i++)
  {
    std::cout << "shader id: " << shaders[0] << "\n";
    glAttachShader(program, shaders[i]);
  }
  glLinkProgram(program);
  glValidateProgram(program);
  SHADER_LOGGER->out("Shaders Linked\n");
  return ME_FINE;
}
