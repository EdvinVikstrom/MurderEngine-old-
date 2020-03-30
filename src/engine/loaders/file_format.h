#ifndef FILE_FORMAT_H
  #define FILE_FORMAT_H

#include "../kernel/kernel.h"
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

      virtual bool recognized(const std::string &file_name, unsigned char* data, uint32_t data_size) = 0;
      virtual std::vector<std::string> get_file_exts() = 0;

      inline me::fformat::format_type getFormatType()
      {
        return type;
      }

    };

    std::vector<file_format*> formats;

    void init();

    me::image* read_image(const std::string &filepath);
    std::vector<me::item*> read_mesh(const std::string &filepath);

  };

};

#endif
