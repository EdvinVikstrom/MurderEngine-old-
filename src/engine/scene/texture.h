#ifndef TEXTURE_H
  #define TEXTURE_H

#define ME_WCOLOR_TYPE_FLOAT                   32
#define ME_WCOLOR_TYPE_RGBA                    128
#define ME_WCOLOR_TYPE_IMAGE                   256

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

  struct image : mem_utils {
    std::string identifier;
    unsigned int imageId;
    unsigned int format;
    unsigned int width, height;
    unsigned char* pixels;

    image(std::string identifier, unsigned int imageId, unsigned int format, unsigned int width, unsigned int height, unsigned char* pixels)
    {
      this->identifier = identifier;
      this->imageId = imageId;
      this->format = format;
      this->width = width;
      this->height = height;
      this->pixels = pixels;
    }

    image() { }

    ~image()
    {
      delete[] pixels;
    }

    long mem_use() override
    {
      return identifier.size() +
      (sizeof(unsigned int) +
      sizeof(unsigned int) +
      sizeof(unsigned int) +
      sizeof(unsigned int) +
      sizeof(unsigned int)) +
      sizeof(pixels);
    }

  };

  // please remove this
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

  struct wcolor : mem_utils { // stands for wide-color. yes i know very stupid
    unsigned int type;
    float v_float;
    // we can save some memory if we make this a pointer
    me::vec4f rgba;
    me::image* image;
    wcolor(me::image* image)
    {
      type = ME_WCOLOR_TYPE_IMAGE;
      this->image = image;
    }
    wcolor(me::vec4f rgba)
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
    ~wcolor()
    {
      // *do not delete image* look in EngineManager.h
    }
    void bind();
    void unbind();
    long mem_use() override
    {
      return sizeof(unsigned int) +
      sizeof(float) +
      (sizeof(me::vec4f)) +
      (image != nullptr ? image->mem_use() : 0);
    }
  };

  struct image_item : item {
    unsigned int image;
    image_item(std::string identifier, me::vec3d position, me::vec3d rotation, me::vec3d scale, me::vec3d origin, unsigned int image) : item(ME_ITEM_TYPE_IMAGE, identifier, position, rotation, scale, origin)
    {
      this->image = image;
    }
  };

};

#endif
