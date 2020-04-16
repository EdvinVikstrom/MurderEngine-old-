#include "glsl_reader.h"
#include "../../../kernel/io/file_reader.h"
#include <vector>

#include <iostream> // remove

int me::glsl_reader::read_shader_file(const char* filepath, MeShaderProgram* program)
{
  me::fileattr* file = me::read_file(filepath);
  file->readFile();
  std::string data = (char*)file->buffer->data;
  std::vector<std::string> lines = me::split_str(data, '\n');
  MeShaderType type = MeShaderType::UNKNOWN_SHADER;
  for (std::string &line : lines)
  {
    if (line=="#end") type = MeShaderType::UNKNOWN_SHADER;
    if (line=="#vertex") { type = MeShaderType::VERTEX; continue; }
    else if (line=="#tessellation") { type = MeShaderType::TESSELLATION; continue; }
    else if (line=="#geometry") { type = MeShaderType::GEOMETRY; continue; }
    else if (line=="#rasterization") { type = MeShaderType::RASTERIZATION; continue; }
    else if (line=="#fragment") { type = MeShaderType::FRAGMENT; continue; }
    else if (line=="#color_blending") { type = MeShaderType::COLOR_BLENDING; continue; }
    else if (line=="#none") { type = MeShaderType::UNKNOWN_SHADER; continue; }
    if (type==MeShaderType::UNKNOWN_SHADER) continue;
    if (program->shaders.count(type))
      program->shaders[type].append(line + "\n");
    else
      program->shaders[type] = std::string(line + "\n");
  }
  return ME_FINE;
}
