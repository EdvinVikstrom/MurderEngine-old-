#include <iostream>
#include "../../EngineManager.h"
#include "../mesh_loader.h"
#include "../../renderer/RendererApi.h"
#include "../../../external/rapidxml.hpp"
#include "../../utilities/StringUtils.h"
#include "../../utilities/ArrayUtils.h"
#include "../../utilities/Logger.h"
#include "collada_parser.h"

me::log* COLLADA_LOGGER = new me::log("ColladaParser", "\e[33m[%N] %T #%M \e[0m");

/* HELPERS */

static std::map<std::string, std::string> sources;

std::string getNodePath(rapidxml::xml_node<>* node)
{
  std::string path = std::string(node->name()) + " < ";
  rapidxml::xml_node<>* parent = node->parent();
  while(parent != 0)
  {
    path.append(std::string(parent->name()) + " < ");
    parent = parent->parent();
  }
  return path;
}

bool processEffectColors(rapidxml::xml_node<>* node, me::wcolor& wcolor)
{
  rapidxml::xml_node<>* color = node->first_node("color");
  rapidxml::xml_node<>* texture = node->first_node("texture");
  rapidxml::xml_node<>* v_float = node->first_node("float");
  if (color != 0)
  {
    std::string sid = color->first_attribute("sid")->value();
    unsigned int argCount;
    std::string* colorArgs = utils::split(color->value(), ' ', argCount);
    if (argCount < 4)
    {
      COLLADA_LOGGER->err(std::string("[x < 4] too few arguments in 'color' in { ") + getNodePath(node) + " }\n");
      return false;
    }
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
  return true;
}

/* PARSER */

bool collada::parse_mesh(rapidxml::xml_node<>* mesh_node, me::mesh* mesh)
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
      mesh->positions.reserve(count/3);
      me::toVec3f(array, &mesh->positions[0], count);
    }
    if (utils::endsWith(sourceId, "normals"))
    {
      mesh->normals.reserve(count/3);
      me::toVec3f(array, &mesh->normals[0], count);
    }
    if (utils::endsWith(sourceId, "map-0"))
    {
      mesh->texCoords.reserve(count/2);
      me::toVec2f(array, &mesh->texCoords[0], count);
    }
    source = source->next_sibling("source");
  }
  return true;
}

bool collada::parse_faces(rapidxml::xml_node<>* mesh_node, me::mesh* mesh)
{
  rapidxml::xml_node<>* triangles_node = mesh_node->first_node("triangles");
  unsigned int faceCount = std::stoi(triangles_node->first_attribute("count")->value());
  //utils::processStringArray(triangles_node->first_node("p")->value(), [&](unsigned int index, std::string arg) {
    //faces[index] = std::stoi(arg);
  //});
  unsigned int argCount;
  std::string* faceArgs = utils::split(triangles_node->first_node("p")->value(), ' ', argCount);
  unsigned int* faces = new unsigned int[argCount];
  for (int i = 0; i < argCount; i++)
    faces[i] = std::stoi(faceArgs[i]);
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
  me::processMeshFaces(mesh, faces, argCount, vertexOffset, normalOffset, texCoordOffset);
  return true;
}

bool collada::parse_effect(rapidxml::xml_node<>* effect_node, collada::effect* effect)
{
  rapidxml::xml_node<>* profile_common = effect_node->first_node("profile_COMMON");
  /* Params */
  rapidxml::xml_node<>* param_node = profile_common->first_node("newparam");
  while(param_node != 0)
  {
    collada::param* param = new collada::param;
    std::string sid = param_node->first_attribute("sid")->value();
    rapidxml::xml_node<>* node = param_node->first_node();
    while(node != 0)
    {
      param->nodes.push_back(new collada::node_tree(node->name(), node->value()));
      node = node->next_sibling();
    }
    param->sid = sid;
    effect->params.push_back(param);
    param_node = param_node->next_sibling("newparam");
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
  return true;
}

bool collada::parse_camera(rapidxml::xml_node<>* camera_node, me::camera* camera)
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
  return true;
}

bool collada::parse_light(rapidxml::xml_node<>* light_node, me::light* light)
{
  rapidxml::xml_node<>* technique_common = light_node->first_node("technique_common");
  rapidxml::xml_node<>* point_node = technique_common->first_node("point");
  rapidxml::xml_node<>* spot_node = technique_common->first_node("spot");
  rapidxml::xml_node<>* directional_node = technique_common->first_node("directional");
  if (point_node != 0)
  {
    unsigned int argCount;
    std::string* colorArgs = utils::split(point_node->first_node("color")->value(), ' ', argCount);
    float alpha = 1.0F;
    if (argCount < 3)
    {
      COLLADA_LOGGER->err(std::string("[x < 3] too few arguments in 'color' in { ") + getNodePath(light_node) + " }\n");
      return false;
    }
    if (argCount > 3)
      alpha = std::stof(colorArgs[3]);
    me::vec4f* color = new me::vec4f(
      std::stof(colorArgs[0]),
      std::stof(colorArgs[1]),
      std::stof(colorArgs[2]),
      alpha);
    /* TODO: */
    double constant_attenuation = std::stod(point_node->first_node("constant_attenuation")->value());
    double linear_attenuation = std::stod(point_node->first_node("linear_attenuation")->value());
    double quadratic_attenuation = std::stod(point_node->first_node("quadratic_attenuation")->value());
  }
  return true;
}

bool collada::parse_scene(rapidxml::xml_node<>* scene_node, std::map<std::string, me::camera*> &cameras, std::map<std::string, me::light*> &lights, std::map<std::string, me::texture*> &textures, std::map<std::string, collada::effect*> &effects, std::map<std::string, me::material*> &materials, std::map<std::string, me::mesh*> &meshes, std::vector<me::item*> &items)
{
  rapidxml::xml_node<>* node = scene_node->first_node("node");
  while(node != 0)
  {
    me::item* item;
    std::string identifier = node->first_attribute("id")->value();
    rapidxml::xml_node<>* matrix_node = node->first_node("matrix");
    rapidxml::xml_node<>* geometry_node = node->first_node("instance_geometry");
    rapidxml::xml_node<>* light_node = node->first_node("instance_light");
    rapidxml::xml_node<>* camera_node = node->first_node("instance_camera");
    me::vec3d* position = new me::vec3d(0, 0, 0);
    me::vec3d* rotation = new me::vec3d(0, 0, 0);
    me::vec3d* scale = new me::vec3d(0, 0, 0);
    if (matrix_node != 0)
    {
      unsigned int argCount;
      std::string* matrixArgs = utils::split(matrix_node->value(), ' ', argCount);
      double matrix[argCount];
      for (int i = 0; i < argCount; i++)
        matrix[i] = std::stod(matrixArgs[i]);
      if (argCount >= 3)
      { position->x = matrix[0]; position->y = matrix[1]; position->z = matrix[2]; }
      if (argCount >= 6)
      { rotation->x = matrix[3]; rotation->y = matrix[4]; rotation->z = matrix[5]; }
      if (argCount >= 9)
      { scale->x = matrix[6]; scale->y = matrix[7]; scale->z = matrix[8]; }
      delete[] matrixArgs;
    }
    if (geometry_node != 0)
    {
      std::string url = std::string(geometry_node->first_attribute("url")->value()).substr(1);
      item = new me::mesh_item(identifier, position, rotation, scale, meshes[url]);
      rapidxml::xml_node<>* bind_material_node = geometry_node->first_node("bind_material");
      if (bind_material_node != 0)
      {
        rapidxml::xml_node<>* technique_common = bind_material_node->first_node("technique_common");
        if (technique_common != 0)
        {
          rapidxml::xml_node<>* instance_material = technique_common->first_node("instance_material");
          if (instance_material != 0)
          {
            std::string target = std::string(instance_material->first_attribute("target")->value()).substr(1);
            ((me::mesh_item*)item)->mesh->material = materials[target];
          }
        }
      }
    }else if (light_node != 0)
    {
      std::string url = std::string(light_node->first_attribute("url")->value()).substr(1);
      item = new me::light_item(identifier, position, rotation, scale, lights[url]);
    }else if (camera_node != 0)
    {
      std::string url = std::string(camera_node->first_attribute("url")->value()).substr(1);
      item = new me::camera_item(identifier, position, rotation, scale, cameras[url]);
    }
    items.push_back(item);
    node = node->next_sibling();
  }
  return true;
}

/* order: textures, effects, materials, geometries */
std::vector<me::item*> collada::loadColladaFile(char* data, unsigned int size, unsigned int& itemCount)
{
  rapidxml::xml_document<> doc;
  doc.parse<0>(data);
  rapidxml::xml_node<>* node = doc.first_node();
  rapidxml::xml_node<>* library_geometries = node->first_node("library_geometries");
  rapidxml::xml_node<>* library_effects = node->first_node("library_effects");
  rapidxml::xml_node<>* library_cameras = node->first_node("library_cameras");
  rapidxml::xml_node<>* library_lights = node->first_node("library_lights");
  rapidxml::xml_node<>* library_visual_scenes = node->first_node("library_visual_scenes");

  std::map<std::string, me::camera*> cameras;
  std::map<std::string, me::light*> lights;
  std::map<std::string, me::texture*> textures;
  std::map<std::string, collada::effect*> effects;
  std::map<std::string, me::material*> materials;
  std::map<std::string, me::mesh*> meshes;

  std::vector<me::item*> items;

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
      if (!parse_light(light_node, light))
        break;
      lights[identifier] = light;
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
      if (!parse_camera(camera_node, camera))
        break;
      cameras[identifier] = camera;
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
      collada::effect* effect = new collada::effect;
      effect->identifier = identifier;
      COLLADA_LOGGER->out(std::string("Parsing material \"") + identifier + "\"\n");
      if (!parse_effect(effect_node, effect))
        break;
      effects[identifier] = effect;
      effect_node = effect_node->next_sibling("effect");
    }
  }

  if (library_geometries != 0)
  {
    /* geometry */
    rapidxml::xml_node<>* geometry = library_geometries->first_node("geometry");
    while(geometry != 0)
    {
      std::string identifier = geometry->first_attribute("id")->value();
      me::mesh* mesh = new me::mesh;
      COLLADA_LOGGER->out(std::string("Parsing mesh \"") + identifier + "\"\n");
      if (!parse_mesh(geometry->first_node("mesh"), mesh))
        break;
      if (!parse_faces(geometry->first_node("mesh"), mesh))
        break;
      meshes[identifier] = mesh;
      geometry = geometry->next_sibling("geometry");
    }
  }
  rapidxml::xml_node<>* scene_node = library_visual_scenes->first_node("visual_scene");
  parse_scene(scene_node, cameras, lights, textures, effects, materials, meshes, items);
  itemCount = items.size();
  COLLADA_LOGGER->out(std::string("Loaded [") + std::to_string(itemCount) + "] object(s)\n");
  return items;
}
