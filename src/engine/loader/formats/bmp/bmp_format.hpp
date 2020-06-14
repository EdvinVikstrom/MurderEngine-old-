#ifndef BMP_FORMAT_HPP
  #define BMP_FORMAT_HPP

#include "../image_format.hpp"

namespace me {

  /* thanks: [http://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm] */
  namespace format {

    enum BMPColorType {
      BMP_COLOR_MONOCHROME = 1,
      BMP_COLOR_BIT4 = 4,
      BMP_COLOR_BIT8 = 8,
      BMP_COLOR_RGB16 = 16,
      BMP_COLOR_RGB24 = 24
    };

    enum BMPCompressionType {
      BMP_COMPRESSION_RGB = 0,
      BMP_COMPRESSION_RLE8 = 1,
      BMP_COMPRESSION_RLE4 = 2
    };

    struct BMPHeader {

      struct header {
        uint16_t signature;        // 'BM' | offset: 0
        uint32_t file_size;        // size of file in bytes | offset: 2
        uint16_t reserved1;        // unused | offset: 6
        uint16_t reserved2;        // unused | offset: 8
        uint32_t data_offset;      // beginning of the bitmap data | offset: 10
      } file;

      struct info_header {
        uint32_t size;             // size of the header | offset: 14
        uint32_t width;            // image width | offset: 18
        uint32_t height;           // image height | offset: 22
        uint16_t planes;           // planes | offset: 26
        uint16_t bits_per_pixel;   // bits per pixel | offset: 28
        uint32_t compression;      // compression type | offset: 30
        uint32_t image_size;       // size of compressed image | offset: 34
        uint32_t x_pixel_per_m;    // x pixel per meter | offset: 38
        uint32_t y_pixel_per_m;    // y pixel per meter | offset: 42
        uint32_t colors_used;      // number of used colors | offset: 46
        uint32_t important_colors; // number of important colors [0: all] | offset: 50
      } info;

    };

    struct BMPFormat : ImageFormat {

      BMPFormat() : ImageFormat(IFF_BMP) { }

      int readImage(me::bytebuff &buffer, me::Image* image, uint64_t flags) override;
      int writeImage(me::bytebuff &buffer, me::Image* image, uint64_t flags) override;
      bool recognized(me::filebuff* file) override;
      std::vector<std::string> getFileExts() override;
      uint64_t supportedFlags() override;

    };

  };

};

#endif
