#include <GL/glew.h>
#include "image_reader.h"

#include <iostream> // remove

extern std::string RENDERER_API_NAME;

unsigned int me::fformat::load_image(me::image* image)
{
  unsigned int id;
  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  unsigned int e_format = 0;
  unsigned int i_format = 0;
  if (image->format==ME_TEX_FORMAT_RGB)
  {
    e_format = GL_RGB8;
    i_format = GL_RGB;
  }else if (image->format==ME_TEX_FORMAT_RGBA)
  {
    e_format = GL_RGBA8;
    i_format = GL_RGBA;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, e_format, image->width, image->height, 0, i_format, GL_UNSIGNED_BYTE, image->pixels);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
  return id;
}
