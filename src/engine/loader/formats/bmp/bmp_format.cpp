#include "bmp_format.h"

int me::format::bmp_format::read_image(me::fileattr &file, me::image* image)
{
  file.readFile();
  me::filebuff& buffer = *file.buffer;
  bmp_header header;
  header.file.signature = buffer._uint16();
  header.file.file_size = buffer._uint32();
  header.file.reserved = buffer._uint32();
  header.file.data_offset = buffer._uint32();

  header.info.size = buffer._uint32();
  header.info.width = buffer._uint32();
  header.info.height = buffer._uint32();
  header.info.planes = buffer._uint16();
  header.info.bits_per_pixel = buffer._uint16();
  header.info.compression = buffer._uint32();
  header.info.image_size = buffer._uint32();
  header.info.x_pixel_per_m = buffer._uint32();
  header.info.y_pixel_per_m = buffer._uint32();
  header.info.colors_used = buffer._uint32();
  header.info.important_colors = buffer._uint32();

  image->identifier = file.filepath;
  image->width = header.info.width;
  image->height = header.info.height;
  uint32_t image_size = image->width * image->height * 3;

  if (header.info.bits_per_pixel==bmp_color_type::MONOCHROME)
  {
    image->format = ME_TEX_FORMAT_BINARY;
    image->depth = 1;
  }else if (header.info.bits_per_pixel==bmp_color_type::BIT4)
  {
    image->format = ME_TEX_FORMAT_GRAY;
    image->depth = 4;
  }else if (header.info.bits_per_pixel==bmp_color_type::BIT8)
  {
    image->format = ME_TEX_FORMAT_GRAY;
    image->depth = 8;
  }else if (header.info.bits_per_pixel==bmp_color_type::RGB16)
  {
    image->format = ME_TEX_FORMAT_RGB;
    image->depth = 16;
  }else if (header.info.bits_per_pixel==bmp_color_type::RGB24)
  {
    image->format = ME_TEX_FORMAT_RGB;
    image->depth = 24;
  }
  image->pixels = new unsigned char[image_size];
  for (unsigned int i = 0; i < image_size; i+=3)
  {
    image->pixels[i + 2] = buffer.data[header.file.data_offset+i];
    image->pixels[i + 1] = buffer.data[header.file.data_offset+i + 1];
    image->pixels[i] = buffer.data[header.file.data_offset+i + 2];
  }
  return ME_FINE;
}

bool me::format::bmp_format::recognized(me::fileattr &file)
{
  return me::str_ends(file.filepath, ".bmp") || (file.buffer->data[0]=='b' && file.buffer->data[1]=='m');
}

std::vector<std::string> me::format::bmp_format::get_file_exts()
{
  return { "bmp" };
}
