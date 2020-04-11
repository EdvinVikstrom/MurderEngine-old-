#include "glsl_reader.h"
#include "../../../kernel/io/file_reader.h"
#include <vector>

int me::glsl_reader::read_shader_file(const char* filepath, me::shader_program* program)
{
  me::fileattr* file = me::read_file(filepath);
  std::string data = (char*)file->buffer->data;
  std::vector<std::string> lines = me::split_str(data, '\n');
  shader_type type = shader_type::NONE;
  for (std::string &line : lines)
  {
    if (line=="#vertex") { type = shader_type::VERTEX; continue; }
    else if (line=="#tessellation") { type = shader_type::TESSELLATION; continue; }
    else if (line=="#geometry") { type = shader_type::GEOMETRY; continue; }
    else if (line=="#rasterization") { type = shader_type::RASTERIZATION; continue; }
    else if (line=="#fragment") { type = shader_type::FRAGMENT; continue; }
    else if (line=="#color_blending") { type = shader_type::COLOR_BLENDING; continue; }
    else if (line=="#none") { type = shader_type::NONE; continue; }
    if (type==shader_type::NONE) continue;
    if (program->shaders.count(type))
      program->shaders[type].append(line + "\n");
    else
      program->shaders[type] = std::string(line + "\n");
  }
  return ME_FINE;
}
