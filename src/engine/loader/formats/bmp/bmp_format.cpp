#include "bmp_format.h"

int me::format::bmp_format::read_image(me::fileattr &file, me::Image* image)
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

  image->info.identifier = file.filepath;
  image->bitmap->width = header.info.width;
  image->bitmap->height = header.info.height;

  if (header.info.bits_per_pixel==bmp_color_type::MONOCHROME)
  {
    // TODO: < 8 bit image
    image->info.format = ME_IMG_FORMAT_BINARY;
    image->bitmap->depth = 8;
  }else if (header.info.bits_per_pixel==bmp_color_type::BIT4)
  {
    image->info.format = ME_IMG_FORMAT_GRAY;
    image->bitmap->depth = 8;
  }else if (header.info.bits_per_pixel==bmp_color_type::BIT8)
  {
    image->info.format = ME_IMG_FORMAT_GRAY;
    image->bitmap->depth = 8;
  }else if (header.info.bits_per_pixel==bmp_color_type::RGB16)
  {
    image->info.format = ME_IMG_FORMAT_RGB;
    image->bitmap->depth = 16;
  }else if (header.info.bits_per_pixel==bmp_color_type::RGB24)
  {
    image->info.format = ME_IMG_FORMAT_RGB;
    image->bitmap->depth = 24;
  }
  uint32_t image_size = image->bitmap->width * image->bitmap->height * me::byte_rate(image->info.format) * (image->bitmap->depth / 8);
  image->bitmap->map = new unsigned char[image_size];
  for (unsigned int i = 0; i < image_size; i+=3)
  {
    image->bitmap->map[i + 2] = buffer.data[header.file.data_offset+i];
    image->bitmap->map[i + 1] = buffer.data[header.file.data_offset+i + 1];
    image->bitmap->map[i] = buffer.data[header.file.data_offset+i + 2];
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
