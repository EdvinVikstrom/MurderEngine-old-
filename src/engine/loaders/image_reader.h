#ifndef IMAGE_READER_H
  #define IMAGE_READER_H

#define ME_TEX_FORMAT_RGB                  87
#define ME_TEX_FORMAT_RGBA                 93
#define ME_TEX_FORMAT_BINARY               74
#define ME_TEX_FORMAT_GRAY                 75

#include "file_format.h"

namespace me {

  namespace fformat {

    class image_reader : public file_format {

    public:

      image_reader() : file_format(me::fformat::format_type::IMAGE) { }

      virtual int read_image(me::fileattr &file, me::image* image) = 0;
      inline int read_file(me::fileattr &file, me::image* image)
      {
        int result = read_image(file, image);
        if (result != ME_FINE)
          return result;
        return ME_FINE;
      }

      virtual bool recognized(me::fileattr &file) = 0;
      virtual std::vector<std::string> get_file_exts() = 0;

    };

    unsigned int load_image(me::image* image);

  };

};

#endif
