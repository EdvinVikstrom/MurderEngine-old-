#include "collada_format.hpp"
#include "../../../math/vector_utils.hpp"
#include "../../../../external/rapidxml.hpp"

static void fix_matrix(me::maths::mat4 &matrix)
{
  float temp1 = matrix.at(0, 3);
  float temp2 = matrix.at(1, 3);
  float temp3 = matrix.at(2, 3);
  
  matrix.m03(matrix.at(3, 0));
  matrix.m13(matrix.at(3, 1));
  matrix.m23(matrix.at(3, 2));
  
  matrix.m30(temp1);
  matrix.m31(temp2);
  matrix.m32(temp3);
}

static int get_wcolor_location(const std::string &string)
{
  if (string=="diffuse")
  return 0;
  else if (string=="specular")
  return 1;
  else if (string=="emission")
  return 2;
  else if (string=="index_of_refraction")
  return 3;
  return -1;
}

static std::string get_texture_path(std::string &url, std::map<std::string, me::format::collada_param> &params)
{
  if (params[url].path == "source")
  return get_texture_path(params[url].value, params);
  return params[url].value;
}

static me::wcolor* process_node_value(rapidxml::xml_node<>* node, me::format::collada_effect* effect, me::ScenePacket* packet)
{
  rapidxml::xml_node<>* value_node = node->first_node();
  std::string node_name = value_node->name();
  if (node_name == "color")
  {
    std::string color_str = value_node->value();
    char** args = me::splitf_str((char*)color_str.c_str(), color_str.size(), 4, ' ');
    me::vec4* vec = new me::vec4(std::stof(args[0]), std::stof(args[1]), std::stof(args[2]), std::stof(args[3]));
    return new me::wcolor(vec);
  }else if (node_name == "texture")
  {
    std::string texture = value_node->first_attribute("texture")->value();
    std::string tex_path = get_texture_path(texture, effect->params);
    return new me::wcolor(packet->images[tex_path]);
  }else if (node_name == "float")
  return new me::wcolor(new float(std::stof(value_node->value())));
  return nullptr;
}

static bool parse_camera_node(me::bytebuff &buffer, rapidxml::xml_node<>* camera_node, me::ScenePacket* packet)
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
    /* common camera info */
    float fov = std::stof(perspective_node->first_node("xfov")->value());
    float aspect_ratio = std::stof(perspective_node->first_node("aspect_ratio")->value());
    double znear = std::stod(perspective_node->first_node("znear")->value());
    double zfar = std::stod(perspective_node->first_node("zfar")->value());
    
    /* creating Camera object */
    me::Camera* camera = new me::Camera;
    camera->identifier = identifier;
    camera->projection = me::CameraProjection::PROJ_PERSPECTIVE;
    camera->focalLength = fov;
    camera->aspectRatio = aspect_ratio;
    camera->znear = znear;
    camera->zfar = zfar;
    
    /* adding camera to "ScenePacket" */
    packet->cameras[identifier] = camera;
  }else if (orthographic_node != nullptr)
  {
    /* more common camera info */
    float xmag = std::stof(orthographic_node->first_node("xmag")->value());
    float aspect_ratio = std::stof(orthographic_node->first_node("aspect_ratio")->value());
    double znear = std::stod(orthographic_node->first_node("znear")->value());
    double zfar = std::stod(orthographic_node->first_node("zfar")->value());
    
    /* creating the orthographic Camera object */
    me::Camera* camera = new me::Camera;
    camera->identifier = identifier;
    camera->projection = me::CameraProjection::PROJ_ORTHOGRAPHIC;
    camera->focalLength = xmag;
    camera->aspectRatio = aspect_ratio;
    camera->znear = znear;
    camera->zfar = zfar;
    
    /* adding the camera to "ScenePacket" */
    packet->cameras[identifier] = camera;
  }
  return true;
}

static bool parse_light_node(me::bytebuff &buffer, rapidxml::xml_node<>* light_node, me::ScenePacket* packet)
{
  std::string identifier = light_node->first_attribute("id")->value();
  rapidxml::xml_node<>* technique_common_node = light_node->first_node("technique_common");
  
  if (technique_common_node == nullptr)
  return false;
  
  /* create Light object */
  me::Light* light = new me::Light;
  light->identifier = identifier;
  
  rapidxml::xml_node<>* point_node = technique_common_node->first_node("point");
  if (point_node != nullptr)
  {
    /* setting up "point" light */
    
    std::string color_str = point_node->first_node("color")->value();
    char** color_str_args = me::splitf_str((char*)color_str.c_str(), color_str.size(), 3, ' ');
    
    /* light color */
    double red = std::stod(color_str_args[0]);
    double green = std::stod(color_str_args[1]);
    double blue = std::stod(color_str_args[2]);
    double power = me::maths::max(me::maths::max(red, green), blue);
    light->rgba = me::vec3(red, green, blue);
    
    light->power = power;
    
    float constant_attenuation = std::stof(point_node->first_node("constant_attenuation")->value());
    float linear_attenuation = std::stof(point_node->first_node("linear_attenuation")->value());
    float quadratic_attenuation = std::stof(point_node->first_node("quadratic_attenuation")->value());
  }
  /* and don't forget to add the Light to the scene:) */
  packet->lights[identifier] = light;
  return true;
}

static bool parse_effect_node(me::bytebuff &buffer, rapidxml::xml_node<>* effect_node, me::ScenePacket* packet, std::map<std::string, me::format::collada_effect*> &effects)
{
  std::string identifier = effect_node->first_attribute("id")->value();
  rapidxml::xml_node<>* profile_common_node = effect_node->first_node("profile_COMMON");
  
  if (profile_common_node == nullptr)
  return false;
  
  /* creating the classic Collada effect */
  me::format::collada_effect* effect = new me::format::collada_effect;
  effect->identifier = identifier;
  
  rapidxml::xml_node<>* newparam_node = profile_common_node->first_node("newparam");
  
  /* setting up all the params */
  while(newparam_node != nullptr)
  {
    std::string sid = newparam_node->first_attribute("sid")->value();
    rapidxml::xml_node<>* type_node = newparam_node->first_node();
    std::string path = type_node->first_node()->name();
    std::string value = type_node->first_node()->value();
    effect->params[sid] = me::format::collada_param(sid, type_node->name(), path, value);
    newparam_node = newparam_node->next_sibling("newparam");
  }
  
  rapidxml::xml_node<>* technique_node = profile_common_node->first_node("technique");
  
  /* shader, material info */
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
  /* oh i almost forgot! add the effect to the scene (NOTE: this is not "ScenePacket") */
  effects[identifier] = effect;
  return true;
}

static bool parse_image_node(me::bytebuff &buffer, rapidxml::xml_node<>* image_node, me::ScenePacket* packet)
{
  std::string identifier = image_node->first_attribute("id")->value();
  rapidxml::xml_node<>* init_from_node = image_node->first_node("init_from");
  if (init_from_node != nullptr)
  {
    /* image file path */
    std::string path = init_from_node->value();
    
    /* is absolute path? */
    bool abs_path = me::is_abs_path(path);
    
    /* fixing the "filepath" */
    std::string filepath = abs_path ? path : (me::to_folder_path(buffer.source) + "/" + path);
    
    /* and maybe add it to the scene */
    packet->images[identifier] = new me::Image(filepath);
  }
  return true;
}

static bool parse_material_node(me::bytebuff &buffer, rapidxml::xml_node<>* material_node, me::ScenePacket* packet, std::map<std::string, me::format::collada_effect*> &effects)
{
  std::string identifier = material_node->first_attribute("id")->value();
  
  /* creating Material object */
  me::Material* material = new me::Material;
  material->identifier = identifier;
  
  rapidxml::xml_node<>* instance_effect_node = material_node->first_node("instance_effect");
  if (instance_effect_node != nullptr)
  {
    /* the "Collada effect" id/url */
    std::string url = instance_effect_node->first_attribute("url")->value();
    /* removing the "#" */
    url = url.substr(1);
    
    me::format::collada_effect* effect = effects[url];
    material->diffuse = effect->diffuse;
    // TODO:
  }
  /* hmm maybe we should add it to the scene */
  packet->materials[identifier] = material;
  return true;
}

static bool parse_geometry_node(me::bytebuff &buffer, rapidxml::xml_node<>* geometry_node, me::ScenePacket* packet)
{
  std::string identifier = geometry_node->first_attribute("id")->value();
  rapidxml::xml_node<>* mesh_node = geometry_node->first_node("mesh");
  rapidxml::xml_node<>* source_node = mesh_node->first_node("source");
  
  /* creating Mesh object */
  me::Mesh* mesh = new me::Mesh;
  mesh->identifier = identifier;
  
  std::map<std::string, std::vector<float>> float_arrays;
  /* going through all float arrays */
  while(source_node != nullptr)
  {
    rapidxml::xml_node<>* float_array_node = source_node->first_node("float_array");
    rapidxml::xml_node<>* technique_common_node = source_node->first_node("technique_common");
    
    if (float_array_node == nullptr || technique_common_node == nullptr)
    break;
    uint32_t array_size = std::stoi(float_array_node->first_attribute("count")->value());
    std::string raw_array = float_array_node->value();
    
    char** splitted_array = me::splitf_str((char*)raw_array.c_str(), raw_array.size(), array_size, ' ');
    
    std::vector<float> float_array;
    std::string array_identifier = source_node->first_attribute("id")->value();
    
    /* allocate enough memory */
    float_array.reserve(array_size);
    
    /* converting the string to float and adding to "float_array" */
    for (uint32_t i = 0; i < array_size; i++)
    float_array.emplace_back(std::stof(splitted_array[i]));
    rapidxml::xml_node<>* accessor_node = technique_common_node->first_node("accessor");
    float_arrays[array_identifier] = float_array;
    source_node = source_node->next_sibling("source");
  }
  rapidxml::xml_node<>* vertices_node = mesh_node->first_node("vertices");
  if (vertices_node != nullptr)
  {
    rapidxml::xml_node<>* input_node = vertices_node->first_node("input");
    std::string id = vertices_node->first_attribute("id")->value();
    std::string source = input_node->first_attribute("source")->value();
    source = source.substr(1);
    float_arrays[id] = float_arrays[source];
  }
  rapidxml::xml_node<>* triangles_node = mesh_node->first_node("triangles");
  if (triangles_node != nullptr)
  mesh->mode = me::Polygon::TRIANGLE;
  while(triangles_node != nullptr)
  {
    rapidxml::xml_node<>* input_node = triangles_node->first_node("input");
    unsigned int size_mul = 0;
    while(input_node != nullptr)
    {
      std::string semantic = input_node->first_attribute("semantic")->value();
      std::string source = input_node->first_attribute("source")->value();
      source = source.substr(1);
      if (semantic=="VERTEX") { me::utils::float_to_vec3_array(float_arrays[source].size(), &float_arrays[source][0], mesh->positions, true); size_mul+=3; }
      else if (semantic=="NORMAL") { me::utils::float_to_vec3_array(float_arrays[source].size(), &float_arrays[source][0], mesh->normals, true); size_mul+=3; }
      else if (semantic=="TEXCOORD") { me::utils::float_to_vec2_array(float_arrays[source].size(), &float_arrays[source][0], mesh->texCoords, true); size_mul+=3; }
      else if (semantic=="COLOR") { me::utils::float_to_vec4_array(float_arrays[source].size(), &float_arrays[source][0], mesh->colors, true);; size_mul+=3; }
      mesh->offset++;
      input_node = input_node->next_sibling("input");
    }
    rapidxml::xml_node<>* faces_node = triangles_node->first_node("p");
    unsigned int face_count = std::stoi(triangles_node->first_attribute("count")->value());
    std::string material_url = triangles_node->first_attribute("material")->value();
    mesh->materials.push_back(packet->materials[material_url]);
    
    std::string raw_face_array = faces_node->value();
    
    unsigned int array_size = face_count*size_mul;
    char** faces = me::splitf_str((char*)raw_face_array.c_str(), raw_face_array.size(), array_size, ' ');
    
    mesh->indices.reserve(array_size);
    for (unsigned int i = 0; i < array_size; i++)
    mesh->indices.emplace_back(std::stoi(faces[i]));
    triangles_node = triangles_node->next_sibling("triangles");
  }
  packet->meshes[identifier] = mesh;
  return true;
}

static bool parse_visual_scene_node(me::bytebuff &buffer, rapidxml::xml_node<>* visual_scene_node, me::ScenePacket* packet)
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
    me::maths::mat4 transform_matrix;
    while(matrix_node != nullptr)
    {
      std::string sid = matrix_node->first_attribute("sid")->value();
      std::string matrix_str = matrix_node->value();
      char** matrix_args = me::splitf_str((char*)matrix_str.c_str(), matrix_str.size(), 4*4, ' ');
      float* matrix = new float[4 * 4];
      for (unsigned char i = 0; i < 16; i++)
      matrix[i] = std::stof(matrix_args[i]);
      if (sid=="transform") { transform_matrix = me::maths::mat4(matrix); }
      matrix_node = matrix_node->next_sibling("matrix");
    }
    fix_matrix(transform_matrix);
    if (instance_geometry_node != nullptr)
    {
      std::string url = instance_geometry_node->first_attribute("url")->value();
      url = url.substr(1);
      
      me::Mesh* mesh = packet->meshes[url];
      mesh->identifier = identifier;
      mesh->transform = me::transform(transform_matrix);
      
    }else if (instance_camera_node != nullptr)
    {
      std::string url = instance_camera_node->first_attribute("url")->value();
      url = url.substr(1);
      
      me::Camera* camera = packet->cameras[url];
      camera->identifier = identifier;
      camera->view_matrix = transform_matrix;
      
    }else if (instance_light_node != nullptr)
    {
      std::string url = instance_light_node->first_attribute("url")->value();
      url = url.substr(1);
      
      me::Light* light = packet->lights[url];
      light->identifier = identifier;
      light->model_matrix = transform_matrix;
      
    }
    node = node->next_sibling("node");
  }
  return true;
}

int me::format::collada_format::load_scene(me::bytebuff &buffer, me::ScenePacket* packet, uint64_t flags)
{
  rapidxml::xml_document<> doc;
  doc.parse<0>((char*) buffer.data[0]);
  std::cout << "--- [Parsed XML data] ---\n";
  rapidxml::xml_node<>* collada_node = doc.first_node();
  
  rapidxml::xml_node<>* library_cameras_node = collada_node->first_node("library_cameras");
  rapidxml::xml_node<>* library_lights_node = collada_node->first_node("library_lights");
  rapidxml::xml_node<>* library_effects_node = collada_node->first_node("library_effects");
  rapidxml::xml_node<>* library_images_node = collada_node->first_node("library_images");
  rapidxml::xml_node<>* library_materials_node = collada_node->first_node("library_materials");
  rapidxml::xml_node<>* library_geometries_node = collada_node->first_node("library_geometries");
  rapidxml::xml_node<>* library_visual_scenes_node = collada_node->first_node("library_visual_scenes");
  
  std::map<std::string, collada_effect*> effects;
  
  if (library_cameras_node != nullptr)
  {
    std::cout << "==> loading camera data\n";
    rapidxml::xml_node<>* camera_node = library_cameras_node->first_node("camera");
    while(camera_node != nullptr)
    {
      parse_camera_node(buffer, camera_node, packet);
      camera_node = camera_node->next_sibling("camera");
    }
  }
  if (library_lights_node != nullptr)
  {
    std::cout << "==> loading light data\n";
    rapidxml::xml_node<>* light_node = library_lights_node->first_node("light");
    while(light_node != nullptr)
    {
      parse_light_node(buffer, light_node, packet);
      light_node = light_node->next_sibling("light");
    }
  }
  if (library_images_node != nullptr)
  {
    std::cout << "==> loading image data\n";
    rapidxml::xml_node<>* image_node = library_images_node->first_node("image");
    while(image_node != nullptr)
    {
      parse_image_node(buffer, image_node, packet);
      image_node = image_node->next_sibling("image");
    }
  }
  if (library_effects_node != nullptr)
  {
    std::cout << "==> loading effect data\n";
    rapidxml::xml_node<>* effect_node = library_effects_node->first_node("effect");
    while(effect_node != nullptr)
    {
      parse_effect_node(buffer, effect_node, packet, effects);
      effect_node = effect_node->next_sibling("effect");
    }
  }
  if (library_materials_node != nullptr)
  {
    std::cout << "==> loading material data\n";
    rapidxml::xml_node<>* material_node = library_materials_node->first_node("material");
    while(material_node != nullptr)
    {
      parse_material_node(buffer, material_node, packet, effects);
      material_node = material_node->next_sibling("material");
    }
  }
  if (library_geometries_node != nullptr)
  {
    std::cout << "==> loading geometry data\n";
    rapidxml::xml_node<>* geometry_node = geometry_node = library_geometries_node->first_node("geometry");
    while(geometry_node != nullptr)
    {
      parse_geometry_node(buffer, geometry_node, packet);
      geometry_node = geometry_node->next_sibling("geometry");
    }
  }
  if (library_visual_scenes_node != nullptr)
  {
    std::cout << "==> loading scene data\n";
    rapidxml::xml_node<>* visual_scene_node = library_visual_scenes_node->first_node("visual_scene");
    while(visual_scene_node != nullptr)
    {
      parse_visual_scene_node(buffer, visual_scene_node, packet);
      visual_scene_node = visual_scene_node->next_sibling("visual_scene");
    }
  }
  std::cout << "scene loaded\n";
  return ME_FINE;
}

bool me::format::collada_format::recognized(me::fileattr &file)
{
  if (file.buffer->data.size() != 0 && me::str_starts(file.filepath, "<?xml"))
  {
    rapidxml::xml_document<> doc;
    doc.parse<0>((char*) &file.buffer->data[0]); // TODO: will maybe produce errors. "data" does not contain the full document bc memory.
    if (std::string(doc.first_node()->name())=="COLLADA")
    return true;
  }
  return me::str_ends(file.filepath, ".dae") || me::str_ends(file.filepath, ".collada");
}

std::vector<std::string> me::format::collada_format::get_file_exts()
{
  return { "dae", "collada" };
}

uint64_t me::format::collada_format::supported_flags()
{
  return 0; // TODO:
}
