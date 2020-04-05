#include "collada_reader.h"
#include "../../../kernel/io/file_reader.h"
#include "../../../scene/scene.h"
#include "../../../utilities/StringUtils.h"
#include "../../../utilities/Logger.h"
#include "../../file_format.h"
#include "../../../../external/rapidxml.hpp"

static me::log* COLLADA = new me::log("Collada",
"\e[33m[%N] %T #%M \e[0m",
"\e[33m[%N] %T #%M \e[0m",
"\e[33m[%N] %T\e[0m \e[31m#%M \e[0m",
"\e[34m[%N] %T #%M \e[0m"
);

static std::string get_texture_path(std::string &url, std::map<std::string, me::fformat::collada_reader::param> &params)
{
  if (params[url].path == "source")
    return get_texture_path(params[url].value, params);
  return params[url].value;
}

static me::wcolor* process_node_value(rapidxml::xml_node<>* node, me::fformat::collada_reader::effect* effect, me::fformat::collada_reader::packet* packet)
{
  rapidxml::xml_node<>* value_node = node->first_node();
  std::string node_name = value_node->name();
  if (node_name == "color")
  {
    std::string color_str = value_node->value();
    char** args = me::splitf_str((char*)color_str.c_str(), color_str.size(), 4, ' ');
    me::vec4f* vec = new me::vec4f(std::stof(args[0]), std::stof(args[1]), std::stof(args[2]), std::stof(args[3]));
    return new me::wcolor(me::wcolor_type::RGBA, vec);
  }else if (node_name == "texture")
  {
    std::string texture = value_node->first_attribute("texture")->value();
    std::string tex_path = get_texture_path(texture, effect->params);
    return new me::wcolor(me::wcolor_type::IMAGE, packet->scene->images[tex_path]);
  }else if (node_name == "float")
    return new me::wcolor(me::wcolor_type::FLOAT, new float(std::stof(value_node->value())));
  return nullptr;
}

static bool parse_camera_node(me::file_state &file, rapidxml::xml_node<>* camera_node, me::fformat::collada_reader::packet* packet)
{
  std::string identifier = camera_node->first_attribute("id")->value();
  rapidxml::xml_node<>* optics_node = camera_node->first_node("optics");
  rapidxml::xml_node<>* technique_common_node = optics_node->first_node("technique_common");

  if (technique_common_node == nullptr)
    return false;

  rapidxml::xml_node<>* perspective_node = technique_common_node->first_node("perspective");
  rapidxml::xml_node<>* orthographic_node = technique_common_node->first_node("orthographic");

  if (perspective_node != nullptr)
  {
    float fov = std::stof(perspective_node->first_node("xfov")->value());
    float aspect_ratio = std::stof(perspective_node->first_node("aspect_ratio")->value());
    double znear = std::stod(perspective_node->first_node("znear")->value());
    double zfar = std::stod(perspective_node->first_node("zfar")->value());
    me::camera* camera = new me::camera;
    camera->identifier = identifier;
    camera->type = me::camera_type::ORTHOGRAPHIC;
    camera->focalLength = fov;
    camera->aspectRatio = aspect_ratio;
    camera->znear = znear;
    camera->zfar = zfar;
    packet->scene->cameras[identifier] = camera;
  }else if (orthographic_node != nullptr)
  {
    float xmag = std::stof(orthographic_node->first_node("xmag")->value());
    float aspect_ratio = std::stof(orthographic_node->first_node("aspect_ratio")->value());
    double znear = std::stod(orthographic_node->first_node("znear")->value());
    double zfar = std::stod(orthographic_node->first_node("zfar")->value());
    me::camera* camera = new me::camera;
    camera->identifier = identifier;
    camera->type = me::camera_type::ORTHOGRAPHIC;
    camera->focalLength = xmag;
    camera->aspectRatio = aspect_ratio;
    camera->znear = znear;
    camera->zfar = zfar;
    packet->scene->cameras[identifier] = camera;
  }
  return true;
}

static bool parse_light_node(me::file_state &file, rapidxml::xml_node<>* light_node, me::fformat::collada_reader::packet* packet)
{
  std::string identifier = light_node->first_attribute("id")->value();
  rapidxml::xml_node<>* technique_common_node = light_node->first_node("technique_common");

  if (technique_common_node == nullptr)
    return false;

  me::light* light = new me::light;
  light->identifier = identifier;

  rapidxml::xml_node<>* point_node = technique_common_node->first_node("point");
  if (point_node != nullptr)
  {
    std::string color_str = point_node->first_node("color")->value();
    char** color_str_args = me::splitf_str((char*)color_str.c_str(), color_str.size(), 3, ' ');
    double red = std::stod(color_str_args[0]);
    double green = std::stod(color_str_args[1]);
    double blue = std::stod(color_str_args[2]);
    me::vec3d color(red, green, blue);
    float constant_attenuation = std::stof(point_node->first_node("constant_attenuation")->value());
    float linear_attenuation = std::stof(point_node->first_node("linear_attenuation")->value());
    float quadratic_attenuation = std::stof(point_node->first_node("quadratic_attenuation")->value());
  }
  packet->scene->lights[identifier] = light;
  return true;
}

static bool parse_effect_node(me::file_state &file, rapidxml::xml_node<>* effect_node, me::fformat::collada_reader::packet* packet)
{
  std::string identifier = effect_node->first_attribute("id")->value();
  rapidxml::xml_node<>* profile_common_node = effect_node->first_node("profile_COMMON");

  if (profile_common_node == nullptr)
    return false;

  me::fformat::collada_reader::effect* effect = new me::fformat::collada_reader::effect;
  effect->identifier = identifier;

  rapidxml::xml_node<>* newparam_node = profile_common_node->first_node("newparam");
  while(newparam_node != nullptr)
  {
    std::string sid = newparam_node->first_attribute("sid")->value();
    rapidxml::xml_node<>* type_node = newparam_node->first_node();
    std::string path = type_node->first_node()->name();
    std::string value = type_node->first_node()->value();
    effect->params[sid] = me::fformat::collada_reader::param(sid, type_node->name(), path, value);
    newparam_node = newparam_node->next_sibling("newparam");
  }

  rapidxml::xml_node<>* technique_node = profile_common_node->first_node("technique");
  if (technique_node != nullptr)
  {
    rapidxml::xml_node<>* phong_node = technique_node->first_node("phong");
    rapidxml::xml_node<>* blinn_node = technique_node->first_node("blinn");
    rapidxml::xml_node<>* lambert_node = technique_node->first_node("lambert");

    rapidxml::xml_node<>* shader_node;
    if (phong_node != nullptr)
      shader_node = phong_node;
    else if (blinn_node != nullptr)
      shader_node = blinn_node;
    else if (lambert_node != nullptr)
      shader_node = lambert_node;
    if (shader_node != nullptr)
    {
      rapidxml::xml_node<>* emission_node = shader_node->first_node("emission");
      rapidxml::xml_node<>* ambient_node = shader_node->first_node("ambient");
      rapidxml::xml_node<>* diffuse_node = shader_node->first_node("diffuse");
      rapidxml::xml_node<>* specular_node = shader_node->first_node("specular");
      rapidxml::xml_node<>* shininess_node = shader_node->first_node("shininess");
      rapidxml::xml_node<>* reflective_node = shader_node->first_node("reflective");
      rapidxml::xml_node<>* reflectivity_node = shader_node->first_node("reflectivity");
      rapidxml::xml_node<>* transparent_node = shader_node->first_node("transparent");
      rapidxml::xml_node<>* transparency_node = shader_node->first_node("transparency");
      rapidxml::xml_node<>* ior_node = shader_node->first_node("index_of_refraction");
      if (emission_node != nullptr) effect->emission = process_node_value(emission_node, effect, packet);
      if (ambient_node != nullptr) effect->ambient = process_node_value(ambient_node, effect, packet);
      if (diffuse_node != nullptr) effect->diffuse = process_node_value(diffuse_node, effect, packet);
      if (specular_node != nullptr) effect->specular = process_node_value(specular_node, effect, packet);
      if (shininess_node != nullptr) effect->shininess = process_node_value(shininess_node, effect, packet);
      if (reflective_node != nullptr) effect->reflective = process_node_value(reflective_node, effect, packet);
      if (reflectivity_node != nullptr) effect->reflectivity = process_node_value(reflectivity_node, effect, packet);
      if (transparent_node != nullptr) effect->transparent = process_node_value(transparent_node, effect, packet);
      if (transparency_node != nullptr) effect->transparency = process_node_value(transparency_node, effect, packet);
      if (ior_node != nullptr) effect->ior = process_node_value(ior_node, effect, packet);
    }
  }
  packet->effects[identifier] = effect;
  return true;
}

static bool parse_image_node(me::file_state &file, rapidxml::xml_node<>* image_node, me::fformat::collada_reader::packet* packet)
{
  std::string identifier = image_node->first_attribute("id")->value();
  rapidxml::xml_node<>* init_from_node = image_node->first_node("init_from");
  if (init_from_node != nullptr)
  {
    std::string path = init_from_node->value();
    bool abs_path = me::is_abs_path(path);
    std::string filepath = abs_path ? path : (me::to_folder_path(file.filepath) + "/" + path);
    me::image* image = me::fformat::read_image(filepath);
    packet->scene->images[identifier] = image;
  }
  return true;
}

static bool parse_material_node(me::file_state &file, rapidxml::xml_node<>* material_node, me::fformat::collada_reader::packet* packet)
{
  std::string identifier = material_node->first_attribute("id")->value();
  me::material* material = new me::material;
  material->identifier = identifier;
  rapidxml::xml_node<>* instance_effect_node = material_node->first_node("instance_effect");
  if (instance_effect_node != nullptr)
  {
    std::string url = instance_effect_node->first_attribute("url")->value();
    url = url.substr(1);
    me::fformat::collada_reader::effect* effect = packet->effects[url];
    material->rgba = effect->diffuse;
    // TODO:
  }
  packet->scene->materials[identifier] = material;
  return true;
}

static bool parse_geometry_node(me::file_state &file, rapidxml::xml_node<>* geometry_node, me::fformat::collada_reader::packet* packet)
{
  std::string identifier = geometry_node->first_attribute("id")->value();
  rapidxml::xml_node<>* mesh_node = geometry_node->first_node("mesh");
  rapidxml::xml_node<>* source_node = mesh_node->first_node("source");
  me::mesh* mesh = new me::mesh;
  mesh->identifier = identifier;
  while(source_node != nullptr)
  {
    rapidxml::xml_node<>* float_array_node = source_node->first_node("float_array");
    std::string source_id = source_node->first_attribute("id")->value();
    uint32_t count = std::stoi(float_array_node->first_attribute("count")->value());
    std::string raw_array = float_array_node->value();
    unsigned int array_size = count;
    char** splitted_array = me::splitf_str((char*)raw_array.c_str(), raw_array.size(), array_size, ' ');
    if (strEndsWith(source_id.c_str(), "positions"))
    {
      mesh->positions = new me::array<me::vec3f*>;
      mesh->positions->allocate_mem(count/3);
      for (uint32_t i = 0; i < array_size; i+=3)
        mesh->positions->values[i/3] = new me::vec3f(std::stof(splitted_array[i]), std::stof(splitted_array[i+1]), std::stof(splitted_array[i+2]));
    }else if (strEndsWith(source_id.c_str(), "normals"))
    {
      mesh->normals = new me::array<me::vec3f*>;
      mesh->normals->allocate_mem(count/3);
      for (uint32_t i = 0; i < array_size; i+=3)
        mesh->normals->values[i/3] = new me::vec3f(std::stof(splitted_array[i]), std::stof(splitted_array[i+1]), std::stof(splitted_array[i+2]));
    }else if (strEndsWith(source_id.c_str(), "map-0"))
    {
      mesh->texCoords = new me::array<me::vec2f*>;
      mesh->texCoords->allocate_mem(count/2);
      for (uint32_t i = 0; i < array_size; i+=2)
        mesh->texCoords->values[i/2] = new me::vec2f(std::stof(splitted_array[i]), std::stof(splitted_array[i+1]));
    }
    // TODO: delete the splitted array
    source_node = source_node->next_sibling("source");
  }
  rapidxml::xml_node<>* triangles_node = mesh_node->first_node("triangles");
  rapidxml::xml_node<>* faces_node = triangles_node->first_node("p");
  unsigned int face_count = std::stoi(triangles_node->first_attribute("count")->value());
  std::string raw_face_array = faces_node->value();
  unsigned int array_size = face_count*9;
  char** faces = me::splitf_str((char*)raw_face_array.c_str(), raw_face_array.size(), array_size, ' ');
  mesh->indices = new me::array<unsigned int*>;
  mesh->indices->allocate_mem(array_size);
  for (unsigned int i = 0; i < array_size; i++)
    mesh->indices->values[i] = new unsigned int(std::stoi(faces[i]));
  packet->scene->meshes[identifier] = mesh;
  return true;
}

static bool parse_visual_scene_node(me::file_state &file, rapidxml::xml_node<>* visual_scene_node, me::fformat::collada_reader::packet* packet)
{
  std::string identifier = visual_scene_node->first_attribute("id")->value();
  rapidxml::xml_node<>* node = visual_scene_node->first_node("node");
  while(node != nullptr)
  {
    std::string identifier = node->first_attribute("id")->value();
    rapidxml::xml_node<>* matrix_node = node->first_node("matrix");
    rapidxml::xml_node<>* instance_camera_node = node->first_node("instance_camera");
    rapidxml::xml_node<>* instance_light_node = node->first_node("instance_light");
    rapidxml::xml_node<>* instance_geometry_node = node->first_node("instance_geometry");
    std::string matrix_str = matrix_node->value();
    char** matrix_args = me::splitf_str((char*)matrix_str.c_str(), matrix_str.size(), 4*4, ' ');
    float** matrix = new float*[4]{
      new float[4],
      new float[4],
      new float[4],
      new float[4]
    };
    unsigned int index = 0;
    for (unsigned char i = 0; i < 4; i++)
    {
      for (unsigned char j = 0; j < 4; j++)
      {
        matrix[i][j] = std::stof(matrix_args[index]);
        index++;
      }
    }
    me::transform transform(matrix, 4, 4);
    while(matrix_node != nullptr)
    {
      std::string sid = matrix_node->first_attribute("sid")->value();
      std::string matrix = matrix_node->value();
      if (sid=="transform") { } // TODO:
      matrix_node = matrix_node->next_sibling("matrix");
    }
    if (instance_geometry_node != nullptr)
    {
      std::string url = instance_geometry_node->first_attribute("url")->value();
      url = url.substr(1);
      rapidxml::xml_node<>* bind_material_node = instance_geometry_node->first_node("bind_material");
      if (bind_material_node != nullptr)
      {
        rapidxml::xml_node<>* technique_common_node = bind_material_node->first_node("technique_common");
        rapidxml::xml_node<>* instance_material_node = technique_common_node->first_node("instance_material");
        std::string target = instance_material_node != nullptr ? instance_material_node->first_attribute("target")->value() : "#####";
        target = target.substr(1); /* we don't like the "#" */
        if (packet->scene->meshes[url]->materials == nullptr)
          packet->scene->meshes[url]->materials = new std::vector<me::material*>;
        packet->scene->meshes[url]->materials->push_back(packet->scene->materials[target]);
      }
      packet->scene->items.push_back(new me::item(identifier, me::item_type::MESH, transform, packet->scene->meshes[url]));
    }else if (instance_camera_node != nullptr)
    {
      std::string url = instance_camera_node->first_attribute("url")->value();
      url = url.substr(1);
      packet->scene->cameras[url]->transform = transform;
    }else if (instance_light_node != nullptr)
    {
      std::string url = instance_light_node->first_attribute("url")->value();
      url = url.substr(1);
      packet->scene->lights[url]->transform = transform;
    }
    node = node->next_sibling("node");
  }
  return true;
}

int me::fformat::collada_reader::read_collada(me::file_state &file, me::fformat::collada_reader::packet* packet)
{
  rapidxml::xml_document<> doc;
  doc.parse<0>((char*)file.data);
  COLLADA->out("Parsed XML data\n");
  rapidxml::xml_node<>* collada_node = doc.first_node();

  rapidxml::xml_node<>* library_cameras_node = collada_node->first_node("library_cameras");
  rapidxml::xml_node<>* library_lights_node = collada_node->first_node("library_lights");
  rapidxml::xml_node<>* library_effects_node = collada_node->first_node("library_effects");
  rapidxml::xml_node<>* library_images_node = collada_node->first_node("library_images");
  rapidxml::xml_node<>* library_materials_node = collada_node->first_node("library_materials");
  rapidxml::xml_node<>* library_geometries_node = collada_node->first_node("library_geometries");
  rapidxml::xml_node<>* library_visual_scenes_node = collada_node->first_node("library_visual_scenes");

  if (library_cameras_node != nullptr)
  {
    COLLADA->out("loading camera data\n");
    rapidxml::xml_node<>* camera_node = library_cameras_node->first_node("camera");
    while(camera_node != nullptr)
    {
      parse_camera_node(file, camera_node, packet);
      camera_node = camera_node->next_sibling("camera");
    }
  }
  if (library_lights_node != nullptr)
  {
    COLLADA->out("loading light data\n");
    rapidxml::xml_node<>* light_node = library_lights_node->first_node("light");
    while(light_node != nullptr)
    {
      parse_light_node(file, light_node, packet);
      light_node = light_node->next_sibling("light");
    }
  }
  if (library_images_node != nullptr)
  {
    COLLADA->out("loading image data\n");
    rapidxml::xml_node<>* image_node = library_images_node->first_node("image");
    while(image_node != nullptr)
    {
      parse_image_node(file, image_node, packet);
      image_node = image_node->next_sibling("image");
    }
  }
  if (library_effects_node != nullptr)
  {
    COLLADA->out("loading effect data\n");
    rapidxml::xml_node<>* effect_node = library_effects_node->first_node("effect");
    while(effect_node != nullptr)
    {
      parse_effect_node(file, effect_node, packet);
      effect_node = effect_node->next_sibling("effect");
    }
  }
  if (library_materials_node != nullptr)
  {
    COLLADA->out("loading material data\n");
    rapidxml::xml_node<>* material_node = library_materials_node->first_node("material");
    while(material_node != nullptr)
    {
      parse_material_node(file, material_node, packet);
      material_node = material_node->next_sibling("material");
    }
  }
  if (library_geometries_node != nullptr)
  {
    COLLADA->out("loading geometry data\n");
    rapidxml::xml_node<>* geometry_node = geometry_node = library_geometries_node->first_node("geometry");
    while(geometry_node != nullptr)
    {
      parse_geometry_node(file, geometry_node, packet);
      geometry_node = geometry_node->next_sibling("geometry");
    }
  }
  if (library_visual_scenes_node != nullptr)
  {
    COLLADA->out("loading scene data\n");
    rapidxml::xml_node<>* visual_scene_node = library_visual_scenes_node->first_node("visual_scene");
    while(visual_scene_node != nullptr)
    {
      parse_visual_scene_node(file, visual_scene_node, packet);
      visual_scene_node = visual_scene_node->next_sibling("visual_scene");
    }
  }
  COLLADA->out("scene loaded\n");
  return ME_FINE;
}

bool me::fformat::collada_reader::recognized(me::file_state &file)
{
  if (strStartsWith(file.filepath.c_str(), "<?xml"))
  {
    rapidxml::xml_document<> doc;
    doc.parse<0>((char*)file.data); // TODO: will maybe produce errors. "data" does not contain the full document bc memory.
    if (std::string(doc.first_node()->name())=="COLLADA")
      return true;
  }
  return strEndsWith(file.filepath.c_str(), ".dae") || strEndsWith(file.filepath.c_str(), ".collada");
}

std::vector<std::string> me::fformat::collada_reader::get_file_exts()
{
  return { "dae", "collada" };
}
