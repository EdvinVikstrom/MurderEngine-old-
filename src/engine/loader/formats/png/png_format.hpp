#ifndef PNG_READER_H
  #define PNG_READER_H

#include "../../image_format.hpp"

namespace me {
  
  namespace format {
    
    enum png_color_type : unsigned char {
      INDEXED,
      GRAYSCALE,
      GRAYSCALE_ALPHA,
      TRUECOLOR,
      TRUECOLOR_ALPHA
    };
    
    enum png_chunk_type : uint32_t {
      PNG_CHUNK_IHDR = 0x49484452,
      PNG_CHUNK_PLTE = 0x504C5445,
      PNG_CHUNK_IDAT = 0x49444154,
      PNG_CHUNK_IEND = 0x49454E44,
      PNG_CHUNK_BKGD = 0x624B4744,
      PNG_CHUNK_CHRM = 0x6348524D,
      PNG_CHUNK_DSIG = 0x64534947,
      PNG_CHUNK_EXIF = 0x65584966,
      PNG_CHUNK_GAMA = 0x67414D41,
      PNG_CHUNK_HIST = 0x68495354,
      PNG_CHUNK_ICCP = 0x69434350,
      PNG_CHUNK_ITXT = 0x69545874,
      PNG_CHUNK_PHYS = 0x70485973,
      PNG_CHUNK_SBIT = 0x73424954,
      PNG_CHUNK_SPLT = 0x73504C54,
      PNG_CHUNK_SRGB = 0x73524742,
      PNG_CHUNK_STER = 0x73544552,
      PNG_CHUNK_TEXT = 0x74455874,
      PNG_CHUNK_TIME = 0x74494D45,
      PNG_CHUNK_TRNS = 0x74524E53,
      PNG_CHUNK_ZTXT = 0x7A545874
    };
    
    struct png_chunk {
      uint32_t length;
      uint32_t type;
      uint8_t* data;
      uint32_t crc;
    };
#include "png_chunks.h"
    
    
    struct png_header {
      uint8_t* signature;
      
    };
    
    struct png_struct {
      png_header header;
      std::map<uint32_t, png_chunk*> chunks;
    };
    
    struct png_format : image_format {
      
      png_format() : image_format(IFF_PNG) { }
      
      int read_header(me::bytebuff &buffer, png_header &header);
      int next_chunk(me::bytebuff &buffer, png_chunk* chunk);
      int read_chunks(me::bytebuff &buffer, std::map<uint32_t, png_chunk*> &chunks);
      
      int load_image(me::bytebuff &buffer, me::Image* image, uint64_t flags) override;
      int write_image(me::bytebuff &buffer, me::Image* image, uint64_t flags) override;
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;
      uint64_t supported_flags() override;
      
    };
    
  };
  
};

#endif
