#include "obj_reader.h"
#include "../../../kernel/io/file_reader.h"
#include "../../../utilities/StringUtils.h"
#include "../../../utilities/Logger.h"

static void load_mtllib(std::string &filepath, std::vector<me::material*> &materials, std::map<std::string, unsigned int> &material_locations)
{
  me::file_state file = me::read_file(filepath);
  std::vector<std::string> lines = me_utils::splitStr((char*)file.data, '\n');
  std::string current_material;
  for (std::string line : lines)
  {
    std::vector<std::string> args = me_utils::splitStr(line, ' ');
    if (args.at(0)=="newmtl")
    {
      current_material = args.at(1);
      me::material* material = new me::material;
      material->identifier = current_material;
      materials.push_back(material);
      material_locations[current_material] = materials.size()-1;
    }
  }
}

int me::fformat::obj_reader::read_obj(me::file_state &file, me::scene_packet* scene)
{
  std::vector<std::string> lines = me_utils::splitStr((char*)file.data, '\n');
  std::string current_obj_name;
  me::mesh* current_mesh;
  std::vector<me::vec3f*>* positions = new std::vector<me::vec3f*>;
  std::vector<me::vec3f*>* normals = new std::vector<me::vec3f*>;
  std::vector<me::vec2f*>* texCoords = new std::vector<me::vec2f*>;
  std::vector<unsigned int*>* indices = new std::vector<unsigned int*>;
  std::vector<me::material*> materials;
  std::map<std::string, unsigned int> material_locations;
  std::vector<unsigned int*> material_indices;

  for (std::string line : lines)
  {
    std::vector<std::string> args = me_utils::splitStr(line, ' ');
    if (args.at(0)=="mtllib")
    {
      bool abs_path = me::is_abs_path(args.at(1));
      std::string filepath = abs_path ? args.at(1) : (file.folder() + "/" + args.at(1));
      load_mtllib(filepath, materials, material_locations);
    }else if (args.at(0)=="o")
    {
      current_obj_name = args.at(1);
      current_mesh = new me::mesh;
    }else if (args.at(0)=="v")
      positions->push_back(new me::vec3f(std::stof(args.at(1)), std::stof(args.at(2)), std::stof(args.at(3))));
    else if (args.at(0)=="vn")
      normals->push_back(new me::vec3f(std::stof(args.at(1)), std::stof(args.at(2)), std::stof(args.at(3))));
    else if (args.at(0)=="vt")
      texCoords->push_back(new me::vec2f(std::stof(args.at(1)), std::stof(args.at(2))));
    else if (args.at(0)=="usemtl")
    {
      std::string mtlid = args.at(1);
      material_indices.push_back(new unsigned int[2]{material_locations[mtlid], indices->size()});
    }else if (args.at(0)=="f")
    {
      std::vector<std::string> x_args = me_utils::splitStr(args.at(1), '/');
      std::vector<std::string> y_args = me_utils::splitStr(args.at(2), '/');
      std::vector<std::string> z_args = me_utils::splitStr(args.at(3), '/');
      unsigned int x_pos = std::stoi(x_args.at(0));
      unsigned int x_nor = std::stoi(x_args.at(1));
      unsigned int x_tex = std::stoi(x_args.at(2));
      unsigned int y_pos = std::stoi(y_args.at(0));
      unsigned int y_nor = std::stoi(y_args.at(1));
      unsigned int y_tex = std::stoi(y_args.at(2));
      unsigned int z_pos = std::stoi(z_args.at(0));
      unsigned int z_nor = std::stoi(z_args.at(1));
      unsigned int z_tex = std::stoi(z_args.at(2));
      indices->push_back(&x_pos);
      indices->push_back(&x_nor);
      indices->push_back(&x_tex);
      indices->push_back(&y_pos);
      indices->push_back(&y_nor);
      indices->push_back(&y_tex);
      indices->push_back(&z_pos);
      indices->push_back(&z_nor);
      indices->push_back(&z_tex);
    }
  }
  return ME_FINE;
}

bool me::fformat::obj_reader::recognized(me::file_state &file)
{
  return me_utils::strEndsWith(file.filepath, ".obj");
}

std::vector<std::string> me::fformat::obj_reader::get_file_exts()
{
  return { "obj", "wavefront" };
}
