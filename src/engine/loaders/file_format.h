#ifndef FILE_FORMAT_H
  #define FILE_FORMAT_H

#include "../kernel/kernel.h"
#include "../kernel/io/file_state.h"
#include "../scene/scene.h"
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

      virtual bool recognized(me::file_state &file) = 0;
      virtual std::vector<std::string> get_file_exts() = 0;

      inline me::fformat::format_type getFormatType()
      {
        return type;
      }

    };

    me::image* read_image(const std::string &filepath);
    me::scene_packet* read_mesh(const std::string &filepath);

    void init();
    void cleanup();

  };

};

#endif
