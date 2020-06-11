#include "shader_loader.hpp"
#include "../kernel/io/filebuff.hpp"

#include "../../external/rapidxml.hpp"
#include <vector>

void me::loadShadersProperties(me::bytebuff &buffer, me::MeShaders &shaders)
{
  rapidxml::xml_document<> doc;
  doc.parse<0>((char*) buffer.data[0]);
  rapidxml::xml_node<>* shaders_node = doc.first_node("shaders");
  rapidxml::xml_node<>* settings_node = shaders_node->first_node("settings");
  rapidxml::xml_node<>* setting_node = settings_node->first_node();

  while (setting_node != nullptr)
  {
    std::string name = setting_node->node_name();
    std::string type = setting_node->first_attribute("type");
    std::string value = setting_node->first_attribute("value");
    me::VarType varType;
    if (type == "byte") varType = VAR_INT8;
    else if (type == "short") varType = VAR_INT16;
    else if (type == "integer") varType = VAR_INT32;
    else if (type == "long") varType = VAR_INT64;
    else if (type == "float") varType = VAR_FLOAT32;
    else if (type == "double") varType = VAR_FLOAT64;
    else if (type == "boolean") varType = VAR_UINT8;
    else if (type == "string") varType = VAR_STRING;
    setting_node = setting_node->next_sibling();
  }

}

void me::loadShaders(const std::string &directory, me::MeShaders &shaders, MeRenderer &renderer)
{
  me::filebuff* shaders_properties = me::loadFile(directory + "shaders_properties.xml").readFile();
  loadShadersProperties(*shaders_properties->buffer);
  loadShaderProgram(directory + "shaders/final", new uint8_t[2]{1, 2}, shaders.program_final, renderer);
  loadShaderProgram(directory + "shaders/ui", new uint8_t[2]{1, 2}, shaders.program_ui, renderer);
}

MeShader me::loadShaderData(uint8_t* data, uint32_t length, uint8_t type, MeRenderer &renderer)
{
  std::vector<std::string> lines = me::split_str(data, '\n');
  std::string formated;
  for (const std::string &line : lines)
  {
    if (me::str_starts(line, "//"))
      continue;
    formated.append(line);
    formated.append("\n");
  }
  MeShader shader = {0, type};
  renderer.compileShader(formated, type, shader);
  return shader;
}

/* double copy, good */
MeShader me::readShaderFile(const std::string &filepath, MeRenderer &renderer)
{
  uint8_t type = 0;
  if (me::str_ends(filepath, ".vsh")) type = 1;
  else if (me::str_ends(filepath, ".fsh")) type = 2;
  me::filebuff* file = me::loadFile(filepath).readFile();
  return loadShaderData(file->buffer->data[0], file->buffer->length, type, renderer);
}

void loadShaderProgram(const std::string &filepath, uint8_t* types, MeShaderProgram &program, MeRenderer &renderer)
{
  std::vector<MeShader> shaders;
  for (uint8_t i = 0; i < sizeof(types); i++)
  {
    std::string ext;
    if (types[i] == 1) ext = ".vsh";
    else if (types[i] == 2) ext = ".fsh";
    shaders.push_back(readShaderFile(filepath + ext, renderer));
  }
  renderer.makeShaderProgram(&shaders[0], shaders.size(), program);
}
