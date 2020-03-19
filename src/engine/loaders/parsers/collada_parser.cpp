#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../MurderEngineCommon.h"
#include "../MurderEngine.h"
#include "../../external/rapidxml.hpp"
#include "../utilities/StringUtils.h"
#include "../utilities/ArrayUtils.h"
#include "../utilities/Logger.h"
#include "ColladaParser.h"

me::log* COLLADA_LOGGER = new me::log("ColladaParser", "\e[33m[%N] %T #%M \e[0m");

/* HELPERS */

static std::map<std::string, std::string> sources;

void processEffectColors(rapidxml::xml_node<>* node, me::wcolor& wcolor)
{
  rapidxml::xml_node<>* color = node->first_node("color");
  rapidxml::xml_node<>* texture = node->first_node("texture");
  rapidxml::xml_node<>* v_float = node->first_node("float");
  if (color != 0)
  {
    std::string sid = color->first_attribute("sid")->value();
    unsigned int colorArgsCount;
    std::string* colorArgs = utils::split(color->value(), ' ', colorArgsCount);
    wcolor.type = ME_WCOLOR_TYPE_RGBA;
    wcolor.rgba = new me::vec4f(
      std::stof(colorArgs[0]),
      std::stof(colorArgs[1]),
      std::stof(colorArgs[2]),
      std::stof(colorArgs[3])
    );
  }else if (texture != 0)
  {
    std::string tex = texture->first_attribute("texture")->value();
    rapidxml::xml_attribute<>* uvMapAtt = texture->first_attribute("texcoord");
    me::uvMap* uvMap = nullptr;
    if (uvMapAtt != 0)
    {
      std::string uvMapId = uvMapAtt->value();
      if (uvMapId!="UVMap")
        uvMap = me::getUvMap(sources[uvMapId]);
    }
    wcolor.type = ME_WCOLOR_TYPE_TEXTURE;
    wcolor.texture = new me::texture(me::getImage(sources[tex]), uvMap);
  }else if (v_float != 0)
  {
    wcolor.type = ME_WCOLOR_TYPE_FLOAT;
    wcolor.v_float = std::stof(v_float->value());
  }
}

/* PARSER */

void collada::parse_mesh(rapidxml::xml_node<>* mesh_node, me::mesh* mesh)
{
  rapidxml::xml_node<>* source = mesh_node->first_node("source");
  while(source != nullptr)
  {
    rapidxml::xml_node<>* float_array = source->first_node("float_array");
    std::string arrayId = float_array->first_attribute("id")->value();
    unsigned int count = std::stoi(float_array->first_attribute("count")->value());
    float* array = new float[count];
    utils::processStringArray(float_array->value(), [&](unsigned int index, std::string arg) {
      array[index] = std::stof(arg);
    });

    std::string sourceId = source->first_attribute("id")->value();
    if (utils::endsWith(sourceId, "positions"))
    {
      mesh->positionCount = count/3;
      mesh->positions = new me::vec3f[count/3];
      me::toVec3f(array, mesh->positions, count);
    }
    if (utils::endsWith(sourceId, "normals"))
    {
      mesh->normalCount = count/3;
      mesh->normals = new me::vec3f[count/3];
      me::toVec3f(array, mesh->normals, count);
    }
    if (utils::endsWith(sourceId, "map-0"))
    {
      mesh->uvMap = new me::uvMap("uvMap", count/2, new me::vec2f[count/2]);
      me::toVec2f(array, mesh->uvMap->texCoords, count);
    }
    source = source->next_sibling("source");
  }
}

void collada::parse_faces(rapidxml::xml_node<>* mesh_node, me::mesh* mesh)
{
  rapidxml::xml_node<>* triangles_node = mesh_node->first_node("triangles");
  unsigned int faceCount = std::stoi(triangles_node->first_attribute("count")->value());
  unsigned int* faces = new unsigned int[faceCount*9]; // 9 = x(v,n,t) = 3 + y(v,n,t) = 3 + z(v,n,t) = 3
  utils::processStringArray(triangles_node->first_node("p")->value(), [&](unsigned int index, std::string arg) {
    faces[index] = std::stoi(arg);
  });
  rapidxml::xml_node<>* input_node = triangles_node->first_node("input");
  int vertexOffset, normalOffset, texCoordOffset;
  while(input_node != 0)
  {
    std::string semantic = input_node->first_attribute("semantic")->value();
    if (semantic=="VERTEX")
      vertexOffset = std::stoi(input_node->first_attribute("offset")->value());
    else if (semantic=="NORMAL")
      normalOffset = std::stoi(input_node->first_attribute("offset")->value());
    else if (semantic=="TEXCOORD")
      texCoordOffset = std::stoi(input_node->first_attribute("offset")->value());
    input_node = input_node->next_sibling("input");
  }
  me::processMesh(mesh, faces, faceCount, vertexOffset, normalOffset, texCoordOffset);
}

void collada::parse_effects(rapidxml::xml_node<>* effect_node, me::material* material)
{
  rapidxml::xml_node<>* profile_common = effect_node->first_node("profile_COMMON");
  rapidxml::xml_node<>* param = profile_common->first_node("newparam");
  while(param != 0)
  {
    std::string sid = param->first_attribute("sid")->value();
    rapidxml::xml_node<>* surface = param->first_node("surface");
    rapidxml::xml_node<>* sampler_2d = param->first_node("sampler2D");
    COLLADA_LOGGER->out(std::string("Parsing material param { sid: \"") + sid + std::string("\", type: ") + std::string(surface!=0?"SURFACE":(sampler_2d!=0?"SAMPLER2D":"NULL")) + " }\n");
    if (surface != 0)
    {
      rapidxml::xml_node<>* init_from = surface->first_node("init_from");
      rapidxml::xml_node<>* source = surface->first_node("source");
      std::string type = surface->first_attribute("type")->value();
      unsigned int texType = type=="2D"?ME_TEXTURE_2D:(type=="3D"?ME_TEXTURE_3D:0);
      std::string texId;
      if (init_from != 0)
        texId = init_from->value();
      else if (source != 0)
        texId = sources[std::string(source->value())];
      sources[sid] = texId;
      COLLADA_LOGGER->out(std::string("Texture identifier \"") + texId + "\"(surface)\n");
      material->surfaces.push_back(me::getTexture(texId));
    }else if (sampler_2d != 0)
    {
      rapidxml::xml_node<>* init_from = sampler_2d->first_node("init_from");
      rapidxml::xml_node<>* source = sampler_2d->first_node("source");
      std::string samplerId;
      if (init_from != 0)
        samplerId = init_from->value();
      else if (source != 0)
        samplerId = sources[std::string(source->value())];
      else
        COLLADA_LOGGER->err("No sampler found\n");
      sources[sid] = samplerId;
      COLLADA_LOGGER->out(std::string("Texture identifier \"") + samplerId + "\"(sampler)\n");
      material->surfaces.push_back(me::getTexture(samplerId));
    }
    param = param->next_sibling("newparam");
  }
  rapidxml::xml_node<>* technique = profile_common->first_node("technique");
  std::string technique_sid = technique->first_attribute("sid")->value();
  rapidxml::xml_node<>* lambert = technique->first_node("lambert");
  rapidxml::xml_node<>* emission = lambert->first_node("emission");
  rapidxml::xml_node<>* diffuse = lambert->first_node("diffuse");
  rapidxml::xml_node<>* index_of_refraction = lambert->first_node("index_of_refraction");
  if (emission != 0)
    processEffectColors(emission, material->emission);
  if (diffuse != 0)
    processEffectColors(diffuse, material->diffuse);
  if (index_of_refraction != 0)
    processEffectColors(index_of_refraction, material->ior);
}

void collada::parse_camera(rapidxml::xml_node<>* camera_node, me::mesh* mesh)
{

}

/* order: textures, effects, materials, geometries */
me::mesh* collada::loadColladaFile(char* data, unsigned int size, unsigned int* meshCount)
{
  rapidxml::xml_document<> doc;
  doc.parse<0>(data);
  rapidxml::xml_node<>* node = doc.first_node();
  rapidxml::xml_node<>* library_geometries = node->first_node("library_geometries");
  rapidxml::xml_node<>* library_effects = node->first_node("library_effects");

  /* effects */
  rapidxml::xml_node<>* effect = library_effects->first_node("effect");
  while(effect != 0)
  {
    std::string identifier = effect->first_attribute("id")->value();
    me::material* material = new me::material(identifier, "shader", {ME_WCOLOR_TYPE_FLOAT, 0}, {ME_WCOLOR_TYPE_FLOAT, 0}, {ME_WCOLOR_TYPE_FLOAT, 0});
    COLLADA_LOGGER->out(std::string("Parsing material \"") + identifier + "\"\n");
    parse_effects(effect, material);
    me::registerMaterial(identifier, material);
    effect = effect->next_sibling("effect");
  }

  /* geometry */
  rapidxml::xml_node<>* geometry = library_geometries->first_node("geometry");
  std::vector<me::mesh*> meshes;
  while(geometry != 0)
  {
    std::string identifier = geometry->first_attribute("id")->value();
    me::mesh* mesh = new me::mesh;
    COLLADA_LOGGER->out(std::string("Parsing mesh \"") + identifier + "\"\n");
    parse_mesh(geometry->first_node("mesh"), mesh);
    COLLADA_LOGGER->out(std::string("Parsing mesh faces \"") + identifier + "\"\n");
    parse_faces(geometry->first_node("mesh"), mesh);
    meshes.push_back(mesh);
    COLLADA_LOGGER->out(std::string("Added mesh to collection \"") + identifier + std::string("\"[") + std::to_string(meshes.size()) + "]\n");
    geometry = geometry->next_sibling("geometry");
  }
  *meshCount = meshes.size();
  COLLADA_LOGGER->out(std::string("Loaded [") + std::to_string(*meshCount) + "] mesh(es)\n");
  return meshes[0];
}
