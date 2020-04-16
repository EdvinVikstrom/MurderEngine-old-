#ifndef FILE_FORMAT_H
  #define FILE_FORMAT_H

#include "../MurderEngine.h"
#include "../kernel/io/file_reader.h"
#include "../scene/scene_content.h"
#include <vector>

namespace me {

  namespace format {

    enum FileType {
      FTYPE_IMAGE = 0,
      FTYPE_MESH = 0,
      FTYPE_AUDIO = 0
    };

    struct file_format {

      me::format::FileType type;

      file_format(me::format::format_type type)
      {
        this->type = type;
      }

      virtual bool recognized(me::fileattr &file) = 0;
      virtual std::vector<std::string> get_file_exts() = 0;

    };

    void read_image(MeInstance* instance, const std::string &filepath, me::image* image);
    void read_mesh(MeInstance* instance, const std::string &filepath, me::scene_packet* packet);

    void init();
    void cleanup();

  };

};

#endif
