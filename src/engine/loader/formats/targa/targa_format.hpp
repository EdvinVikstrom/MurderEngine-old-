#ifndef TARGA_FORMAT_H
  #define TARGA_FORMAT_H

#include "../../image_format.hpp"

namespace me {

  namespace format {

    enum targa_version : unsigned char {
      TARGA_V1_0 = 1,
      TARGA_V2_0 = 2
    };

    enum targa_image_type : unsigned char {
      TARGA_IMG_TYPE_UNCOMPRESSED_COLOR = 1,
      TARGA_IMG_TYPE_UNCOMPRESSED_TRUE_COLOR = 2,
      TARGA_IMG_TYPE_UNCOMPRESSED_GRAYSCALE = 3,
      TARGA_IMG_TYPE_RUN_LENGTH_COLOR = 9,
      TARGA_IMG_TYPE_RUN_LENGTH_TRUE_COLOR = 10,
      TARGA_IMG_TYPE_RUN_LENGTH_GRAYSCALE = 11
    };

    struct targa_color_map_spec {
      uint16_t entryIndex;
      uint16_t mapLength;
      uint8_t mapEntrySize;
    };

    struct targa_image_spec {
      uint16_t xOrigin;
      uint16_t yOrigin;
      uint16_t width;
      uint16_t height;
      uint8_t pixelDepth;
      uint8_t imageDescriptor;
    };

    struct targa_ext_area {
      uint16_t size;
      uint8_t* authorName;
      uint8_t* authorComment;
      uint8_t* dateTime;
      uint8_t* jobId;
      uint8_t* jobTime;
      uint8_t* softwareId;
      uint8_t* softwareVersion;
      uint32_t keyColor;
      uint32_t aspectRatio;
      uint32_t gamma;
      uint32_t colorCorrectionOffset;
      uint32_t postageStampOffset;
      uint32_t scanLineOffset;
      uint8_t attribType;
    };

    struct targa_header {
      uint8_t idLength;
      uint8_t colorMapType;
      uint8_t imageType;
      targa_color_map_spec colorMapSpec;
      targa_image_spec imageSpec;
    };

    struct targa_format : image_format {

      targa_format() : image_format(IFF_TARGA) { }

      int read_extension_area(me::bytebuff &buffer, targa_ext_area &ext_area);
      int read_header(me::bytebuff &buffer, targa_header &header);
      int decode(me::bytebuff &buffer, me::Image* image, targa_header &header);

      int load_image(me::bytebuff &buffer, me::Image* image, uint64_t flags) override;
      int write_image(me::bytebuff &buffer, me::Image* image, uint64_t flags) override;
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;
      uint64_t supported_flags() override;

    };

  };

};

#endif