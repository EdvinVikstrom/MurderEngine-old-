#ifndef JPEG_READER_H
  #define JPEG_READER_H

#include "../../image_format.hpp"

namespace me {

  namespace format {

    enum jpeg_marker_type : unsigned char {
      JPEG_MARKER_SOI = 0xD8,
      JPEG_MARKER_DHT = 0xC4,
      JPEG_MARKER_DQT = 0xDB,
      JPEG_MARKER_DRI = 0xDD,
      JPEG_MARKER_SOS = 0xDA,
      JPEG_MARKER_RST = 0xD0,
      JPEG_MARKER_SOF = 0xC0,
      JPEG_MARKER_APP = 0xE0,
      JPEG_MARKER_COM = 0xFE,
      JPEG_MARKER_EOI = 0xD9
    };

    struct jpeg_marker {
      uint16_t identifier;
      uint16_t length;
      uint8_t* info;

      inline void read(me::bytebuff &buffer)
      {
        identifier = buffer.pull_uint16();
        length = buffer.pull_uint16();
        info = buffer.pull(new uint8_t[length], length);
      }

    };

    struct jpeg_header {
      uint16_t SOI;
      jpeg_marker DHT;
      jpeg_marker DQT;
      jpeg_marker DRI;
      jpeg_marker SOS;
      uint16_t RST[8];
      jpeg_marker SOF[16];
      jpeg_marker APP[16];
      jpeg_marker COM;
      uint16_t EOI;
    };

    struct jpeg_format : image_format {

      jpeg_format() : image_format(IFF_JPEG) { }

      int read_header(me::bytebuff &buffer, jpeg_header &header);

      int load_image(me::bytebuff &buffer, me::Image* image, uint64_t flags) override;
      int write_image(me::bytebuff &buffer, me::Image* image, uint64_t flags) override;
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;
      uint64_t supported_flags() override;

    };

  };

};

#endif