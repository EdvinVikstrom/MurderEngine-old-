#ifndef TEXTURE_H
  #define TEXTURE_H

#include <atomic>
#include <cstdint>
#include "metadata.h"

#define IMAGE_MAX_WIDTH                    44100
#define IMAGE_MAX_HEIGHT                   44100

namespace me {

  enum ImageFormat : unsigned char {
    ME_IMG_FORMAT_RGB =                    0x03,
    ME_IMG_FORMAT_RGBA =                   0x14,
    ME_IMG_FORMAT_BINARY =                 0x21,
    ME_IMG_FORMAT_GRAY =                   0x31,
    ME_IMG_FORMAT_GRAY_ALPHA =             0x42
  };

  enum ImageCompression : unsigned char {
    ME_IMG_COMPRESSION_NONE =              0x1,
    ME_IMG_COMPRESSION_DEFLATE =           0x2,
    ME_IMG_COMPRESSION_LZW =               0x3,
    ME_IMG_COMPRESSION_PACK_BITS =         0x4,
    ME_IMG_COMPRESSION_DWAA =              0x5,
    ME_IMG_COMPRESSION_PXR24 =             0x6,
    ME_IMG_COMPRESSION_B44A =              0x7,
    ME_IMG_COMPRESSION_B44 =               0x8,
    ME_IMG_COMPRESSION_CCITT3 =            0x9,
    ME_IMG_COMPRESSION_CCITT4 =            0x10,
    ME_IMG_COMPRESSION_CCITT6 =            0x11
  };

  enum VideoCodec : unsigned char {
    ME_VID_CODEC_H264 =                   0xF1,
    ME_VID_CODEC_MPEG4 =                  0xF2,
    ME_VID_CODEC_PNG =                    0xF3
  };

  enum WColorType : unsigned char {
    ME_WCOLOR_MAP = 0,
    ME_WCOLOR_COLOR = 1,
    ME_WCOLOR_FLOAT = 2
  };

  struct Bitmap {
    uint32_t width, height;
    unsigned char bitsPerSample;
    unsigned char* map;
  };

  struct ImageInfo {
    uint32_t data[4];
    std::string source;
    std::string identifier;
    me::metadata* metadata = new me::metadata;
    ImageFormat format;
    ImageCompression compression = ME_IMG_COMPRESSION_NONE;
  };

  struct Image {

    Bitmap* bitmap;
    ImageInfo info;

    Image(Bitmap* bitmap, ImageInfo info)
    {
      this->bitmap = bitmap;
      this->info = info;
    }

    Image(std::string source)
    {
      info.source = source;
    }

    Image() { }

    ~Image()
    {
    }

  };

  struct ImageSequence {

    std::string source;
    std::string identifier;

    uint32_t frameCount;
    uint32_t fps;
    ImageFormat imageFormat;
    std::vector<Bitmap*> frames;

    ImageSequence(std::string source, std::string identifier)
    {
      this->source = source;
      this->identifier = identifier;
    }

    ImageSequence(std::string source, std::string identifier, uint32_t frameCount, uint32_t fps, ImageFormat format)
    {
      this->source = source;
      this->identifier = identifier;
      this->frameCount = frameCount;
      this->fps = fps;
      this->imageFormat = imageFormat;
    }

    ImageSequence() { }

    ~ImageSequence() { }

    bool hasNext();
    Bitmap* nextFrame();

  };

  struct wcolor { // stands for wide-color. yes i know very stupid

    unsigned char type;
    void* data;

    wcolor(me::Image* image)
    {
      type = WColorType::ME_WCOLOR_MAP;
      this->data = image;
    }

    wcolor(me::vec4* color)
    {
      type = WColorType::ME_WCOLOR_COLOR;
      this->data = color;
    }

    wcolor(float* f)
    {
      type = WColorType::ME_WCOLOR_FLOAT;
      this->data = f;
    }

    wcolor()
    {
    }

    ~wcolor()
    {
    }

  };

  struct ImageRasterizer {

    me::Image* image;

    ImageRasterizer(me::Image* image)
    {
      this->image = image;
    }

/*
    inline void set_pixel(int color, int posX, int posY)
    {
      if (posX < 0 || posX >= image->bitmap->width || posY < 0 || posY >= image->bitmap->height)
        return;
      uint32_t index = (posY * image->bitmap->width + posX) * (image->bitmap->depth / 8);
      unsigned char red = (unsigned char)(color >> 24);
      unsigned char green = (image->info.format & 0x0F) > 1 ? (unsigned char)(color >> 16) : red;
      unsigned char blue = (image->info.format & 0x0F) > 2 ? (unsigned char)(color >> 8) : green;
      unsigned char alpha = (image->info.format & 0x0F) > 3 ? (unsigned char)color : blue;
      image->bitmap->map[index] = red;
      if ((image->info.format & 0x0F) > 1)
        image->bitmap->map[index + 1] = green;
      if ((image->info.format & 0x0F) > 2)
        image->bitmap->map[index + 2] = blue;
      if ((image->info.format & 0x0F) > 3)
        image->bitmap->map[index + 3] = alpha;
    }

    inline int get_pixel(int posX, int posY)
    {
      if (posX < 0 || posX >= image->bitmap->width || posY < 0 || posY >= image->bitmap->height)
        return 0x00000000;
      uint32_t index = (posY * image->bitmap->width + posX) * (image->bitmap->depth / 8);
      return (image->bitmap->map[index] << 24) | (image->bitmap->map[index + 1] << 16) | (image->bitmap->map[index + 2] << 8) | (image->bitmap->map[index + 3]);
    }

    inline void fill_rect(int color, int posX, int posY, uint32_t scaleX, uint32_t scaleY)
    {
      for (uint32_t x = 0; x < scaleX; x++)
      {
        for (uint32_t y = 0; y < scaleY; y++)
          set_pixel(color, posX + x, posY + y);
      }
    }

    inline void flip_vertical()
    {
      for (uint32_t y = 0; y < image->bitmap->height / 2; y++)
      {
        for (uint32_t x = 0; x < image->bitmap->width; x++)
        {
          int temp = get_pixel(x, image->bitmap->height - y - 1);
          int color = get_pixel(x, y);
          set_pixel(color, x, image->bitmap->height - y - 1);
          set_pixel(temp, x, y);
        }
      }
    }
*/

  };

};

#endif
