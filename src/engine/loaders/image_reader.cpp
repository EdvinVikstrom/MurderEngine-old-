#include <GL/glew.h>
#include <string>
#include "../utilities/StringUtils.h"
#include "../utilities/FileUtils.h"
#include "../utilities/Logger.h"
#include "../math/vectors.h"
  #include "../scene/scene.h"
#include "../renderer/renderer_api.h"
#include "formats.h"
#include "ImageReader.h"

static me::log* IMAGE_LOGGER = new me::log("ImageReader",
"\e[30m[%N] %T #%M \e[0m",
"\e[30m[%N] %T\e[0m \e[33m#%M \e[0m",
"\e[30m[%N] %T\e[0m \e[31m#%M \e[0m",
"\e[34m[%N] %T #%M \e[0m"
);

// helpers
static unsigned int getImageFormat(unsigned short bitsPerPixel)
{
  if (bitsPerPixel==8)
    return ME_TEX_FORMAT_GRAY8;
  else if (bitsPerPixel==16)
    return ME_TEX_FORMAT_GRAY16;
  else if (bitsPerPixel==24)
    return ME_TEX_FORMAT_RGB8;
  else if (bitsPerPixel==32)
    return ME_TEX_FORMAT_RGBA8;
  return 0;
}

me::image* readPNG(char* data, unsigned int size)
{
  return nullptr;
}

me::image* readBMP(char* data, unsigned int size)
{
  IMAGE_LOGGER->out("--Reading BMP Image data--\n");
  unsigned int index = 0;
  // header [14 bytes]
  unsigned int pixelArrayIndex = ((data[10]&0xFF)) | ((data[11]&0xFF) << 8) | ((data[12]&0xFF) << 16) | ((data[13]&0xFF) << 24);
  index+=14;
  // dib header [7 bytes]
  index+=7;
  // extra bit masks [12 or 16 bytes]
  unsigned int width = ((data[18]&0xFF)) | ((data[19]&0xFF) << 8) | ((data[20]&0xFF) << 16) | ((data[21]&0xFF) << 24);
  unsigned int height = ((data[22]&0xFF)) | ((data[23]&0xFF) << 8) | ((data[24]&0xFF) << 16) | ((data[25]&0xFF) << 24);
  unsigned short bitsPerPixel = ((data[28]&0xFF)) | ((data[29]&0xFF) << 8);

  IMAGE_LOGGER->out(std::string("  Size: ") + std::to_string(width) + ", " + std::to_string(height) + "\n");
  IMAGE_LOGGER->out(std::string("  BitsPerPixel: ") + std::to_string(bitsPerPixel) + "\n");

  unsigned int pixelCount = width*height*(bitsPerPixel/8);
  unsigned char* pixels = new unsigned char[pixelCount];
  for (unsigned int i = 0; i < pixelCount; i++)
    pixels[i] = data[pixelArrayIndex+i];
  return new me::image("", ME_TEXTURE_2D, 0, getImageFormat(bitsPerPixel), width, height, pixels);
}

me::image* readRAW(char* data, unsigned int size)
{
  short width = ((data[1]&0xFF)) | ((data[0]&0xFF) << 8);
  short height = ((data[3]&0xFF)) | ((data[2]&0xFF) << 8);
  unsigned char* pixels = new unsigned char[width*height*4];
  for (unsigned int i = 4; i < size; i++)
    pixels[i-4] = (data[i]);
  return new me::image("", ME_TEXTURE_2D, 0, ME_TEX_FORMAT_RGB8, width, height, pixels); // TODO: Image Id, Image Format
}

unsigned int me::createImageId(me::image* image)
{
  unsigned int id;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  unsigned int e_format = 0;
  unsigned int i_format = 0;
  if (image->format==ME_TEX_FORMAT_RGB8)
  {
    e_format = GL_RGB8;
    i_format = GL_RGB;
  }else if (image->format==ME_TEX_FORMAT_RGBA8)
  {
    e_format = GL_RGBA8;
    i_format = GL_RGBA;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, e_format, image->width, image->height, 0, i_format, GL_UNSIGNED_BYTE, image->pixels);
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
  else if (format==ME_FILE_FORMAT_BMP)
    image = readBMP(data, size);
  else if (format==ME_FILE_FORMAT_PNG)
    image = readPNG(data, size);
  image->imageId = createImageId(image);
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
