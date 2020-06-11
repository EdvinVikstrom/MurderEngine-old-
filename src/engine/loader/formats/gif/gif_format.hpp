#ifndef GIF_FORMAT_H
  #define GIF_FORMAT_H

#include "../../image_format.hpp"

namespace me {

  namespace format {

    struct gif_header {
      unsigned char* signature; // 6 bytes
      uint16_t width;
      uint16_t height;
      uint8_t packedFields;
      bool globalColorTableFlag;
      uint8_t colorResolution;
      uint8_t sortFlag;
      uint32_t nGCTEntries;
      uint32_t bgColorIndex;
      uint8_t pixelAspectRatio;
    };

    struct gif_format : image_format {

      gif_format() : image_format(IFF_GIF) { }

      int load_image(me::bytebuff &buffer, me::Image* image, uint64_t flags) override;
      int write_image(me::bytebuff &buffer, me::Image* image, uint64_t flags) override;
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;
      uint64_t supported_flags() override;

    };

  };

};

#endif