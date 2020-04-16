#ifndef FILE_FORMAT_H
  #define FILE_FORMAT_H

#include "../MurderEngine.h"
#include "../kernel/io/file_reader.h"
#include "../scene/scene_content.h"
#include <vector>

namespace me {

  namespace fformat {

    enum format_type {
      IMAGE = 0,
      MESH = 0,
      AUDIO = 0
    };

    class file_format {

    private:

      me::fformat::format_type type;

    public:


      file_format(me::fformat::format_type type)
      {
        this->type = type;
      }

      virtual bool recognized(me::fileattr &file) = 0;
      virtual std::vector<std::string> get_file_exts() = 0;

      inline me::fformat::format_type getFormatType()
      {
        return type;
      }

    };

    void read_image(MeInstance* instance, const std::string &filepath, me::image* image);
    void read_mesh(MeInstance* instance, const std::string &filepath, me::scene_packet* packet);

    void init();
    void cleanup();

  };

};

#endif
