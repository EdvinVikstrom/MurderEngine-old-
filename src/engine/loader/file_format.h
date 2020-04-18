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
      FTYPE_SCENE = 1,
      FTYPE_AUDIO = 2
    };

    struct file_format {

      me::format::FileType type;

      file_format(me::format::FileType type)
      {
        this->type = type;
      }

      virtual bool recognized(me::fileattr &file) = 0;
      virtual std::vector<std::string> get_file_exts() = 0;

    };

    void loadImage(MeInstance* instance, const std::string &filepath, me::Image* image);
    void loadScene(MeInstance* instance, const std::string &filepath, me::ScenePacket* packet);

    void init();
    void cleanup();

  };

};

#endif
