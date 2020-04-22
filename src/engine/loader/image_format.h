#ifndef IMAGE_READER_H
  #define IMAGE_READER_H

#include "file_format.h"

namespace me {

  namespace format {

    enum ImageFileFormat {
      IFF_PNG,
      IFF_JPEG,
      IFF_GIF,
      IFF_TIFF,
      IFF_BMP,
      IFF_EXR,
      IFF_HDR,
      IFF_RAW
    };

    struct image_format : file_format {

      ImageFileFormat format;

      image_format(ImageFileFormat format) : file_format(me::format::FileType::FTYPE_IMAGE)
      {
         this->format = format;
      }

      virtual int load_image(me::fileattr &file, me::Image* image) = 0;
      virtual bool recognized(me::fileattr &file) = 0;
      virtual std::vector<std::string> get_file_exts() = 0;

    };

  };

};

#endif
