#ifndef ICO_FORMAT_H
  #define ICO_FORMAT_H

#include "../../image_format.h"

namespace me {

  namespace format {

    enum ico_image_type : unsigned char {
      ICO_TYPE_ICON = 1,
      ICO_TYPE_CURSOR = 2
    };

    enum ico_format_type {
      ICO_FORMAT_BMP,
      ICO_FORMAT_PNG
    };

    struct ico_dir_entry {
      uint8_t imageWidth;
      uint8_t imageHeight;
      uint8_t nColors;
      uint8_t reserved;
      union {
        uint16_t planes;
        uint16_t xOffset;
      };
      union {
        uint16_t bitsPerPixel;
        uint16_t yOffset;
      };
      uint32_t imageSize;
      uint32_t offset;
    };

    struct ico_header {
      uint16_t reserved;
      uint16_t type;
      uint16_t nImages; // why 16 bit? why do i need 65000+ images when the image size is max 256?
      ico_dir_entry* entries;
    };

    struct ico_format : image_format {

      ico_format() : image_format(IFF_ICO) { }

      int next_entry(me::bytebuff &buffer, ico_dir_entry &entry);
      int read_header(me::bytebuff &buffer, ico_header &header);

      int load_image(me::bytebuff &buffer, me::Image* image, uint64_t flags) override;
      int write_image(me::bytebuff &buffer, me::Image* image, uint64_t flags) override;
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;
      uint64_t supported_flags() override;

    };

  };

};

#endif
