#include "image_format.hpp"

#include "bmp/bmp_format.hpp"

static std::vector<me::format::ImageFormat*> formats;

void me::format::initImageFormats()
{
  formats.push_back(new BMPFormat());
}

void me::format::cleanupImageFormats()
{
  for (me::format::ImageFormat* format : formats)
    delete format;
  formats.clear();
}

int me::reader::readImage(const std::string &filepath, me::Image* image, uint64_t flags)
{
  me::filebuff* file = me::loadFile(filepath)->readFile();
  me::format::ImageFileFormat format = me::format::ImageFileFormat::IFF_RAW;
  for (me::format::ImageFormat* imageFormat : formats)
  {
    if (imageFormat->recognized(file))
    {
      format = imageFormat->format;
      break;
    }
  }
  return readImage(file->buffer, format, image, flags);
}

int me::reader::readImage(me::bytebuff* buffer, me::format::ImageFileFormat format, me::Image* image, uint64_t flags)
{
  for (me::format::ImageFormat* imageFormat : formats)
  {
    if (imageFormat->format == format)
      return imageFormat->readImage(*buffer, image, flags);
  }
  return ME_FORMAT_NOT_FOUND;
}

int me::writer::writeImage(me::bytebuff* buffer, me::format::ImageFileFormat format, me::Image* image, uint64_t flags)
{
  for (me::format::ImageFormat* imageFormat : formats)
  {
    if (imageFormat->format == format)
      return imageFormat->writeImage(*buffer, image, flags);
  }
  return ME_FORMAT_NOT_FOUND;
}
