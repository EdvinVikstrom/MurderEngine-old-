#ifndef COLLADA_READER_H
  #define COLLADA_READER_H

#include "../../../../external/rapidxml.hpp"
#include "../../scene_format.hpp"

namespace me {
  
  namespace format {
    
    struct collada_param {
      std::string sid;
      std::string type;
      std::string path;
      std::string value;
      
      collada_param(std::string sid, std::string type, std::string path, std::string value)
      {
        this->sid = sid;
        this->type = type;
        this->path = path;
        this->value = value;
      }
      
      collada_param() { }
      
    };
    
    struct collada_effect {
      std::string identifier;
      std::map<std::string, collada_param> params;
      wcolor
      *emission,
      *ambient,
      *diffuse,
      *specular,
      *shininess,
      *reflective,
      *reflectivity,
      *transparent,
      *transparency,
      *ior;
    };
    
    struct collada_format : scene_format {
      
      collada_format() : scene_format(SFF_COLLADA) { }
      
      int load_scene(me::bytebuff &buffer, me::ScenePacket* scene, uint64_t flags) override;
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;
      uint64_t supported_flags() override;
      
    };
    
  };
  
};

#endif
