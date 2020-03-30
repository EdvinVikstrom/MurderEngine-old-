#ifndef COLLADA_READER_H
  #define COLLADA_READER_H

#include "../../../../external/rapidxml.hpp"

namespace me {

  namespace fformat {

    class collada_reader {

    public:

      struct effect {
        std::map<std::string, me::element> params;
        wcolor
        *emission,
        *ambient,
        *diffuse,
        *specular,
        *shininess,
        *reflective,
        *reflectivity,
        *transparent,
        *transparency;
      };

      bool parse_mesh(rapidxml::xml_node<>* mesh_node, me::mesh* mesh);
      bool parse_faces(rapidxml::xml_node<>* mesh_node, me::mesh* mesh);
      bool parse_effect(rapidxml::xml_node<>* effect_node, std::map<std::string, unsigned int> images, collada::effect* effect);
      bool parse_camera(rapidxml::xml_node<>* camera_node, me::camera* camera);
      bool parse_light(rapidxml::xml_node<>* light_node, me::light* light);
      bool parse_scene(rapidxml::xml_node<>* scene_node, std::map<std::string, unsigned int> &cameras, std::map<std::string, unsigned int> &lights, std::map<std::string, unsigned int> &images, std::map<std::string, collada::effect*> &effects, std::map<std::string, unsigned int> &materials, std::map<std::string, unsigned int> &meshes, std::vector<me::item*> &items);

      int read_mesh(const std::string &file_name, unsigned char* data, uint32_t data_size, me::mesh* mesh, std::vector<me::item*> &items) override;
      bool recognized(const std::string &file_name, unsigned char* data, uint32_t data_size) override;
      std::vector<std::string> get_file_exts() override;

    }

  };

};

#endif
