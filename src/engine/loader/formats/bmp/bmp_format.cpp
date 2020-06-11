#include "bmp_format.hpp"

int me::format::BMPFormat::readImage(me::bytebuff &buffer, me::Image* image, uint64_t flags)
{
  BMPHeader header;
  header.file.signature = buffer.pull_uint16();
  header.file.file_size = buffer.pull_uint32();
  header.file.reserved1 = buffer.pull_uint16();
  header.file.reserved2 = buffer.pull_uint16();
  header.file.data_offset = buffer.pull_uint32();

  header.info.size = buffer.pull_uint32();
  header.info.width = buffer.pull_uint32();
  header.info.height = buffer.pull_uint32();
  header.info.planes = buffer.pull_uint16();
  header.info.bits_per_pixel = buffer.pull_uint16();
  header.info.compression = buffer.pull_uint32();
  header.info.image_size = buffer.pull_uint32();
  header.info.x_pixel_per_m = buffer.pull_uint32();
  header.info.y_pixel_per_m = buffer.pull_uint32();
  header.info.colors_used = buffer.pull_uint32();
  header.info.important_colors = buffer.pull_uint32();

  image->bitmap->width = header.info.width;
  image->bitmap->height = header.info.height;

  if (header.info.bits_per_pixel==bmp_color_type::MONOCHROME)
  {
    // TODO: < 8 bit image
    image->info.format = ME_IMG_FORMAT_BINARY;
    image->bitmap->bitsPerSample = 1;
  }else if (header.info.bits_per_pixel==bmp_color_type::BIT4)
  {
    image->info.format = ME_IMG_FORMAT_GRAY;
    image->bitmap->bitsPerSample = 4;
  }else if (header.info.bits_per_pixel==bmp_color_type::BIT8)
  {
    image->info.format = ME_IMG_FORMAT_GRAY;
    image->bitmap->bitsPerSample = 8;
  }else if (header.info.bits_per_pixel==bmp_color_type::RGB16)
  {
    image->info.format = ME_IMG_FORMAT_RGB;
    image->bitmap->bitsPerSample = 8;
  }else if (header.info.bits_per_pixel==bmp_color_type::RGB24)
  {
    image->info.format = ME_IMG_FORMAT_RGB;
    image->bitmap->bitsPerSample = 8;
  }
  std::cout << "[BMPLoader]: width: " << image->bitmap->width << ", height: " << image->bitmap->height << " | bits per sample: " << (int) image->bitmap->bitsPerSample << "\n";
  unsigned short byte_per_pixel = (image->bitmap->bitsPerSample / 8) * image->info.format & 0x00FF;
  uint32_t image_size = image->bitmap->width * image->bitmap->height * byte_per_pixel;
  image->bitmap->map = new unsigned char[image_size];
  for (unsigned int i = 0; i < image_size; i+=3)
  {
    image->bitmap->map[i + 2] = buffer.data[header.file.data_offset+i];
    image->bitmap->map[i + 1] = buffer.data[header.file.data_offset+i + 1];
    image->bitmap->map[i] = buffer.data[header.file.data_offset+i + 2];
  }
  return ME_FINE;
}

int me::format::BMPFormat::writeImage(me::bytebuff &buffer, me::Image* image, uint64_t flags)
{
  uint32_t size = image->bitmap->width * image->bitmap->height * ((image->bitmap->bitsPerSample / 8) * image->info.format & 0x00FF);
  uint32_t header_size = 14 + 40;
  buffer.byteOrder(me::ByteOrder::BO_BIG_ENDIAN);
  buffer.push((unsigned char*) "BM", 2);
  buffer.push_uint32(header_size + size); // file size
  buffer.push_uint32(0); // reserved
  buffer.push_uint32(header_size); // data Offset

  buffer.push_uint32(40); // header size // signed
  buffer.push_uint32((int) image->bitmap->width); // image width // signed
  buffer.push_uint32((int) image->bitmap->height); // image height // signed
  buffer.push_uint16(1); // planes
  buffer.push_uint16(image->bitmap->bitsPerSample); // bits per pixel
  buffer.push_uint32(0); // compression type
  buffer.push_uint32(0); // compressed image size
  buffer.push_uint32((int) image->bitmap->width / 4); // x pixel per meter // signed
  buffer.push_uint32((int) image->bitmap->height / 4); // y pixel per meter // signed
  buffer.push_uint32(0); // colors used
  buffer.push_uint32(0); // important colors
  buffer.pushMem(size);
  for (uint32_t i = 0; i < size; i+=3)
  {
    buffer.push(image->bitmap->map[i + 2]);
    buffer.push(image->bitmap->map[i + 1]);
    buffer.push(image->bitmap->map[i]);
  }
  return ME_FINE;
}

bool me::format::BMPFormat::recognized(me::filebuff* file)
{
  return me::str_ends(file->filepath, ".bmp") || (file.buffer->data.size() >= 2 && file->buffer->data[0]=='b' && file->buffer->data[1]=='m');
}

std::vector<std::string> me::format::BMPFormat::getFileExts()
{
  return { "bmp" };
}

uint64_t me::format::BMPFormat::supportedFlags()
{
  return 0; // TODO:
}
