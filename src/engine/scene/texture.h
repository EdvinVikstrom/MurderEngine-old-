#ifndef TEXTURE_H
  #define TEXTURE_H

#define ME_WCOLOR_TYPE_FLOAT                   0x32
#define ME_WCOLOR_TYPE_RGBA                    0x128
#define ME_WCOLOR_TYPE_IMAGE                   0x256

namespace me {

  struct uvMap {
    std::string identifier;
    unsigned int count;
    me::vec2f* texCoords;

    uvMap(std::string identifier, unsigned int count, me::vec2f* texCoords)
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

  struct wcolor { // stands for wide-color. yes i know very stupid
    unsigned int type;
    float v_float;
    me::vec4f* rgba;
    me::image* image;
    wcolor(me::image* image)
    {
      type = ME_WCOLOR_TYPE_IMAGE;
      this->image = image;
    }
    wcolor(me::vec4f* rgba)
    {
      type = ME_WCOLOR_TYPE_RGBA;
      this->rgba = rgba;
    }
    wcolor(float v_float)
    {
      type = ME_WCOLOR_TYPE_FLOAT;
      this->v_float = v_float;
    }
    wcolor()
    {
      
    }
  };

};

#endif
