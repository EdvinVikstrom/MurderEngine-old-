#ifndef TEXTURE_H
  #define TEXTURE_H

#define ME_TEX_FORMAT_RGB                  3
#define ME_TEX_FORMAT_RGBA                 4
#define ME_TEX_FORMAT_BINARY               1
#define ME_TEX_FORMAT_GRAY                 1

#include <atomic>
#include <cstdint>
#include "metadata.h"

namespace me {

  enum wcolor_type {
    ME_WCOLOR_MAP = 0,
    ME_WCOLOR_COLOR = 1,
    ME_WCOLOR_FLOAT = 2
  };

  struct image {
    std::string source;
    std::string identifier;
    me::metadata* metadata;
    unsigned int imageId;
    unsigned int bindId;
    unsigned int format;
    unsigned int depth;
    unsigned int width, height;
    unsigned char* pixels;

    bool loaded = false;

    image(std::string source, std::string identifier, me::metadata* metadata, unsigned int bindId, unsigned int format, unsigned int depth, unsigned int width, unsigned int height, unsigned char* pixels)
    {
      this->source = source;
      this->identifier = identifier;
      this->metadata = metadata;
      this->bindId = bindId;
      this->format = format;
      this->depth = depth;
      this->width = width;
      this->height = height;
      this->pixels = pixels;
    }

    image(std::string source)
    {
      this->source = source;
    }

    image() { }

    ~image()
    {
      delete[] pixels;
    }

  };

  struct wcolor { // stands for wide-color. yes i know very stupid

    int type = 0;

    me::image* image;
    me::vec4 color;
    float f;

    wcolor(me::image* image)
    {
      type = 0;
      this->image = image;
    }

    wcolor(me::vec4 color)
    {
      type = 1;
      this->color = color;
    }

    wcolor(float f)
    {
      type = 2;
      this->f = f;
    }

    wcolor()
    {
    }

    ~wcolor()
    {
    }

  };

};

#endif
