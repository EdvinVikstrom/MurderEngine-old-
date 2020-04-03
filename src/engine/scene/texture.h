#ifndef TEXTURE_H
  #define TEXTURE_H

#include <atomic>
#include <cstdint>

namespace me {

  enum wcolor_type {
    IMAGE = 0,
    RGBA = 1,
    FLOAT = 2
  };

  struct image {
    std::string identifier;
    unsigned int imageId;
    unsigned int format;
    unsigned int depth;
    unsigned int width, height;
    unsigned char* pixels;

    image(std::string identifier, unsigned int imageId, unsigned int format, unsigned int depth, unsigned int width, unsigned int height, unsigned char* pixels)
    {
      this->identifier = identifier;
      this->imageId = imageId;
      this->format = format;
      this->depth = depth;
      this->width = width;
      this->height = height;
      this->pixels = pixels;
    }

    image() { }

    ~image()
    {
      delete[] pixels;
    }

  };

  struct wcolor { // stands for wide-color. yes i know very stupid
    /* TODO: std::atomic */
    wcolor_type type;
    me::image* v_image;
    me::vec4f* v_rgba;
    float* v_float;
    wcolor(wcolor_type type, me::image* v_image)
    {
      this->type = type;
      this->v_image = v_image;
    }
    wcolor(wcolor_type type, me::vec4f* v_rgba)
    {
      this->type = type;
      this->v_rgba = v_rgba;
    }
    wcolor(wcolor_type type, float* v_float)
    {
      this->type = type;
      this->v_float = v_float;
    }
    wcolor()
    {

    }
    ~wcolor()
    {
      // *do not delete image* look in EngineManager.h
    }
    void bind();
    void unbind();
  };

};

#endif
