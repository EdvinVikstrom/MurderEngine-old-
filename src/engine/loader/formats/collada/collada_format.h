#ifndef COLLADA_READER_H
  #define COLLADA_READER_H

#include "../../../../external/rapidxml.hpp"
#include "../../scene_format.h"

namespace me {

  namespace format {

    struct collada_format : public scene_format {

      struct param {
        std::string sid;
        std::string type;
        std::string path;
        std::string value;

        param(std::string sid, std::string type, std::string path, std::string value)
        {
          this->sid = sid;
          this->type = type;
          this->path = path;
          this->value = value;
        }

        param() { }

      };

      struct effect {
        std::string identifier;
        std::map<std::string, param> params;
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

      struct packet {
        me::ScenePacket* scene;
        std::map<std::string, effect*> effects;
      };

      int read_collada(me::fileattr &file, packet* packet);
      int read_scene(me::fileattr &file, me::ScenePacket* scene) override
      {
        return read_collada(file, new packet{scene});
      }
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;

    };

  };

};

#endif
