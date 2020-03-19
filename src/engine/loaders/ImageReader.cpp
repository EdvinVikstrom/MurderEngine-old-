#include <iostream> // remove
#include "GL/glew.h"
#include "../MurderEngineCommon.h"
#include "ImageReader.h"
#include "../utilities/StringUtils.h"
#include "../utilities/Logger.h"
#include "../utilities/FileUtils.h"
#include "../MurderEngine.h"

me::image* readPNG(char* data, unsigned int size)
{
  return nullptr;
}

me::image* readRAW(char* data, unsigned int size)
{
  short width = ((data[1]&0xFF)) | ((data[0]&0xFF) << 8);
  short height = ((data[3]&0xFF)) | ((data[2]&0xFF) << 8);
  unsigned char* pixels = new unsigned char[width*height*4];
  for (unsigned int i = 4; i < size; i++)
    pixels[i-4] = (data[i]);
  return new me::image("", ME_TEXTURE_2D, 0, ME_TEX_FORMAT_RGBA8, width, height, pixels); // TODO: Image Id, Image Format
}

unsigned int me::createImageId(me::image* image)
{
  unsigned int id;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

  glBindTexture(GL_TEXTURE_2D, 0);
  return id;
}

me::image* me::loadImage(const char* path, unsigned int format)
{
  unsigned int size = 0;
  char* data = file_utils_read(path, size);
  me::image* image = nullptr;
  if (format==ME_FILE_FORMAT_RAW)
    image = readRAW(data, size);
  image->texId = createImageId(image);
  return image;
}

me::image* me::loadImage(const char* path)
{
  unsigned int format = 0;
  if (utils::endsWith(path, "png")) format = ME_FILE_FORMAT_PNG;
  else if (utils::endsWith(path, "jpg") || utils::endsWith(path, "jpeg")) format = ME_FILE_FORMAT_JPEG;
  else if (utils::endsWith(path, "gif")) format = ME_FILE_FORMAT_GIF;
  else if (utils::endsWith(path, "bmp")) format = ME_FILE_FORMAT_BMP;
  else if (utils::endsWith(path, "raw")) format = ME_FILE_FORMAT_RAW;
  return loadImage(path, format);

}

void me::initImageReader()
{
}
