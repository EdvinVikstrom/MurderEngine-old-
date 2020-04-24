#ifndef BMP_READER_H
  #define BMP_READER_H

#include "../../image_format.h"

namespace me {

  /* thanks: [http://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm] */
  namespace format {

    enum bmp_color_type {
      MONOCHROME = 1,
      BIT4 = 4,
      BIT8 = 8,
      RGB16 = 16,
      RGB24 = 24
    };

    enum bmp_compression_type {
      BI_RGB = 0,
      BI_RLE8 = 1,
      BI_RLE4 = 2
    };

    struct bmp_header {

      struct header {
        uint16_t signature;        // 'BM' | offset: 0
        uint32_t file_size;        // size of file in bytes | offset: 2
        uint32_t reserved;         // unused | offset: 6
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

    struct bmp_format : image_format {

      bmp_format() : image_format(IFF_BMP) { }

      int load_image(me::fileattr &file, me::Image* image) override;
      int write_image(me::bytebuff &buffer, me::Image* image) override;
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;

    };

  };

};

#endif
