#ifndef IMAGE_READER_H
  #define IMAGE_READER_H

#include "file_format.h"

namespace me {

  namespace format {

    struct image_format : public file_format {

    public:

      image_format() : file_format(me::format::FileType::FTYPE_IMAGE) { }

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

  };

};

#endif
