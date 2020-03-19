#ifndef TEXTURE_H
  #define TEXTURE_H

#define ME_WCOLOR_TYPE_FLOAT                   0x32
#define ME_WCOLOR_TYPE_RGBA                    0x128
#define ME_WCOLOR_TYPE_TEXTURE                 0x256

#include <string>
#include "../math/vectors.h"

namespace me {

  struct uvMap {
    std::string identifier;
    unsigned int count;
    vec2f* texCoords;

    uvMap(std::string identifier, unsigned int count, vec2f* texCoords)
    {
      this->identifier = identifier;
      this->count = count;
      this->texCoords = texCoords;
    }

    ~uvMap()
    {

    }

  };

  struct image {
    std::string identifier;
    unsigned int type;
    unsigned int texId;
    unsigned int format;
    unsigned int width, height;
    unsigned char* pixels;

    image(std::string identifier, unsigned int type, unsigned int texId, unsigned int format, unsigned int width, unsigned int height, unsigned char* pixels)
    {
      this->identifier = identifier;
      this->type = type;
      this->texId = texId;
      this->format = format;
      this->width = width;
      this->height = height;
      this->pixels = pixels;
    }

    ~image()
    {

    }

  };

  struct texture {
    me::image* image;
    me::uvMap* uvMap;

    texture(me::image* image, me::uvMap* uvMap)
    {
      this->image = image;
      this->uvMap = uvMap;
    }

    ~texture()
    {

    }

  };

  struct wcolor {
    unsigned int type;
    float v_float;
    me::vec4f* rgba;
    me::texture* texture;
  };

};

#endif
