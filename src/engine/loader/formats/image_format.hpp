#ifndef IMAGE_READER_H
  #define IMAGE_READER_H

#include "../../scene/texture.hpp"
#include "file_format.hpp"

namespace me {

  namespace format {

    struct ImageFormat {

      ImageFileFormat format;

      image_format(ImageFileFormat format)
      {
         this->format = format;
      }

      virtual int readImage(me::bytebuff &buffer, me::Image* image, uint64_t flags) = 0;
      virtual int writeImage(me::bytebuff &buffer, me::Image* image, uint64_t flags) = 0;
      virtual bool recognized(me::filebuff* file) = 0;
      virtual std::vector<std::string> getFileExts() = 0;
      virtual uint64_t supportedFlags() = 0;

    };

    void initImageFormats();
    void cleanupImageFormats();

  };

  namespace reader {

    int readImage(const std::string &filepath, me::Image* image, uint64_t flags);
    int readImage(me::bytebuff* buffer, me::format::ImageFileFormat format, me::Image* image, uint64_t flags);

  };

  namespace writer {

    int writeImage(me::bytebuff* buffer, me::format::ImageFileFormat format, me::Image* image, uint64_t flags);

  };

};

#endif
