#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../../EngineManager.h"
#include "../mesh_loader.h"
#include "../../renderer/RendererApi.h"
#include "../../../external/rapidxml.hpp"
#include "../../utilities/StringUtils.h"
#include "../../utilities/ArrayUtils.h"
#include "../../utilities/Logger.h"
#include "../../math/vectors.h"
#include "../../scene/camera.h"
#include "../../scene/light.h"
#include "collada_parser.h"

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
    wcolor.rgba = new me::vec4f(std::stof(colorArgs[0]), std::stof(colorArgs[1]), std::stof(colorArgs[2]), std::stof(colorArgs[3]));
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
  me::processMeshFaces(mesh, faces, faceCount, vertexOffset, normalOffset, texCoordOffset);
}

void collada::parse_effect(rapidxml::xml_node<>* effect_node, collada::effect* effect)
{
  collada::effect* effect = new collada::effect;
  rapidxml::xml_node<>* profile_common = effect_node->first_node("profile_COMMON");
  /* Params */
  rapidxml::xml_node<>* param = profile_common->first_node("newparam");
  while(param != 0)
  {
    collada::param* param = new collada::param;
    std::string sid = param->first_attribute("sid")->value();
    rapidxml::xml_node<>* node = param->first_node();
    while(node != 0)
    {
      param->nodes.push_back(new collada::node_tree(node->name(), node->value()));
      node = node->next_sibling();
    }
    param->sid = sid;
    effect->params.push_back(param);
    param = param->next_sibling("newparam");
  }
  rapidxml::xml_node<>* technique = profile_common->first_node("technique");
  rapidxml::xml_node<>* lambert = technique->first_node("lambert");

  rapidxml::xml_node<>* emission_node = lambert->first_node("emission");
  rapidxml::xml_node<>* diffuse_node = lambert->first_node("diffuse");
  rapidxml::xml_node<>* reflectivity_node = lambert->first_node("reflectivity");
  rapidxml::xml_node<>* transparent_node = lambert->first_node("transparent");
  rapidxml::xml_node<>* index_of_refraction_node = lambert->first_node("index_of_refraction");

  if (emission_node != 0)
    processEffectColors(emission_node, effect->emission);
  if (diffuse_node != 0)
    processEffectColors(diffuse_node, effect->diffuse);
  if (reflectivity_node != 0)
    processEffectColors(reflectivity_node, effect->reflectivity);
  if (transparent_node != 0)
    processEffectColors(transparent_node, effect->transparent);
  if (index_of_refraction_node != 0)
    processEffectColors(index_of_refraction_node, effect->index_of_refraction);
}

void collada::parse_camera(rapidxml::xml_node<>* camera_node, me::camera* camera)
{
  rapidxml::xml_node<>* optics = camera_node->first_node("optics");
  rapidxml::xml_node<>* technique_common = optics->first_node("technique_common");
  rapidxml::xml_node<>* perspective = technique_common->first_node("perspective");
  if (perspective != 0)
  {
    camera->focalLength = std::stof(perspective->first_node("xfov")->value());
    camera->aspectRatio = std::stof(perspective->first_node("aspect_ratio")->value());
    camera->znear = std::stod(perspective->first_node("znear")->value());
    camera->zfar = std::stod(perspective->first_node("zfar")->value());
    camera->type = ME_CAMERA_PERSPECTIVE;
  }
  std::cout << focalLength << ", " << aspectRatio << ", " << znear << ", " << zfar << "\n";
}

void collada::parse_light(rapidxml::xml_node<>* light_node, me::light* light)
{
  rapidxml::xml_node<>* technique_common = light_node->first_node("technique_common");
  rapidxml::xml_node<>* point_node = technique_common->first_node("point");
  rapidxml::xml_node<>* spot_node = technique_common->first_node("spot");
  rapidxml::xml_node<>* directional_node = technique_common->first_node("directional");
  if (point_node != 0)
  {
    std::vector<std::string> colorArgs = utils::split(point_node->first_node("color")->value(), ' ');
    me::vec4f* color = new me::vec4f(
      std::stof(colorArgs.at(0)),
      std::stof(colorArgs.at(1)),
      std::stof(colorArgs.at(2)),
      std::stof(colorArgs.at(3)));
    /* TODO: */
    double constant_attenuation = std::stod(point_node->first_node("constant_attenuation")->value());
    double linear_attenuation = std::stod(point_node->first_node("linear_attenuation")->value());
    double quadratic_attenuation = std::stod(point_node->first_node("quadratic_attenuation")->value());
  }
}

/* order: textures, effects, materials, geometries */
me::scene_content* collada::loadColladaFile(char* data, unsigned int size, unsigned int& itemCount)
{
  rapidxml::xml_document<> doc;
  doc.parse<0>(data);
  rapidxml::xml_node<>* node = doc.first_node();
  rapidxml::xml_node<>* library_geometries = node->first_node("library_geometries");
  rapidxml::xml_node<>* library_effects = node->first_node("library_effects");
  rapidxml::xml_node<>* library_cameras = node->first_node("library_cameras");
  rapidxml::xml_node<>* library_lights = node->first_node("library_lights");

  std::vector<camera*> cameras;
  std::vector<light*> lights;
  std::vector<effect*> textures;
  std::vector<effect*> effects;
  std::vector<effect*> materials;
  std::vector<mesh*> meshes;

  /* lights */
  if (library_lights != 0)
  {
    rapidxml::xml_node<>* light_node = library_lights->first_node("light");
    while(light_node != 0)
    {
      std::string identifier = light_node->first_attribute("id")->value();
      me::light* light = new me::light;
      light->identifier = identifier;
      COLLADA_LOGGER->out(std::string("Parsing light \"") + identifier + "\"\n");
      parse_light(light_node, light);
      lights.push_back(light);
      light_node = light_node->next_sibling("light");
    }
  }

  /* cameras */
  if (library_cameras != 0)
  {
    rapidxml::xml_node<>* camera_node = library_cameras->first_node("camera");
    while(camera_node != 0)
    {
      std::string identifier = camera_node->first_attribute("id")->value();
      me::camera* camera = new me::camera;
      camera->identifier = identifier;
      COLLADA_LOGGER->out(std::string("Parsing camera \"") + identifier + "\"\n");
      parse_camera(camera_node, camera);
      cameras.push_back(camera);
      camera_node = camera_node->next_sibling("camera");
    }
  }

  if (library_effects != 0)
  {
    /* effects */
    rapidxml::xml_node<>* effect_node = library_effects->first_node("effect");
    while(effect_node != 0)
    {
      std::string identifier = effect_node->first_attribute("id")->value();
      me::effect* effect = new me::effect;
      effect->identifier = identifier;
      COLLADA_LOGGER->out(std::string("Parsing material \"") + identifier + "\"\n");
      parse_effects(effect_node, material);
      effects.push_back(effect);
      effect_node = effect_node->next_sibling("effect");
    }
  }

  if (library_effects != 0)
  {
    /* geometry */
    rapidxml::xml_node<>* geometry = library_geometries->first_node("geometry");
    while(geometry != 0)
    {
      std::string identifier = geometry->first_attribute("id")->value();
      me::mesh* mesh = new me::mesh;
      COLLADA_LOGGER->out(std::string("Parsing mesh \"") + identifier + "\"\n");
      parse_mesh(geometry->first_node("mesh"), mesh);
      parse_faces(geometry->first_node("mesh"), mesh);
      meshes.push_back(mesh);
      geometry = geometry->next_sibling("geometry");
    }
  }
  itemCount = cameras.size()+textures.size()+effects.size()+materials.size()+meshes.size();
  me:scene_content* content = new scene_content {
    cameras,
    materials,
    textures,
    meshes
  };
  COLLADA_LOGGER->out(std::string("Loaded [") + std::to_string(*meshCount) + "] object(s)\n");
  return content;
}
