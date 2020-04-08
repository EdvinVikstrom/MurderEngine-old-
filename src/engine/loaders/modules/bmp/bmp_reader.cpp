#include "bmp_reader.h"
#include "../../../kernel/common/byte_buffer.h"
#include "../../../utilities/StringUtils.h"

int me::fformat::bmp_reader::read_image(me::file_state &file, me::image* image)
{
  me::byte_buffer buffer(file.data, file.length);
  bmp_header header;
  header.file.signature = buffer.uint16();
  header.file.file_size = buffer.uint32();
  header.file.reserved = buffer.uint32();
  header.file.data_offset = buffer.uint32();

  header.info.size = buffer.uint32();
  header.info.width = buffer.uint32();
  header.info.height = buffer.uint32();
  header.info.planes = buffer.uint16();
  header.info.bits_per_pixel = buffer.uint16();
  header.info.compression = buffer.uint32();
  header.info.image_size = buffer.uint32();
  header.info.x_pixel_per_m = buffer.uint32();
  header.info.y_pixel_per_m = buffer.uint32();
  header.info.colors_used = buffer.uint32();
  header.info.important_colors = buffer.uint32();

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
    image->pixels[i + 2] = file.data[header.file.data_offset+i];
    image->pixels[i + 1] = file.data[header.file.data_offset+i + 1];
    image->pixels[i] = file.data[header.file.data_offset+i + 2];
  }
  return ME_FINE;
}

bool me::fformat::bmp_reader::recognized(me::file_state &file)
{
  return strEndsWith(file.filepath.c_str(), ".bmp") || (file.data[0]=='b' && file.data[1]=='m');
}

std::vector<std::string> me::fformat::bmp_reader::get_file_exts()
{
  return { "bmp" };
}
