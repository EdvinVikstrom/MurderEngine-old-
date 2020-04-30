#include "meimg_format.h"

int me::format::meimg_format::load_image(me::fileattr &file, me::Image* image)
{
  return ME_FINE;
}

int me::format::meimg_format::write_image(me::bytebuff &buffer, me::Image* image)
{
  buffer.push("MEIMG", 5);
  buffer.push_uint16(image->bitmap->width);
  buffer.push_uint16(image->bitmap->height);
  buffer.push(image->bitmap->depth);
  buffer.push(image->info.format);
  buffer.push(image->info.compression);

  me::metadata* meta = image->info.metadata;
  buffer.push(meta != nullptr ? meta->tags.size() : 0);
  if (meta != nullptr)
  {
    for (auto const &[key, value] : meta->tags)
    {
      buffer.push_uint16(key.size());
      buffer.push((unsigned char*) key.c_str(), key.size());
      buffer.push_uint16(value.size());
      buffer.push((unsigned char*) value.c_str(), value.size());
    }
  }
  uint32_t size = image->bitmap->width * image->bitmap->height * (image->bitmap->depth / 8);
  buffer.push_uint32(size);
  buffer.push(image->bitmap->map, size);
  return ME_FINE;
}

bool me::format::meimg_format::recognized(me::fileattr &file)
{
  return me::str_ends(file.filepath, ".meimg");
}

std::vector<std::string> me::format::meimg_format::get_file_exts()
{
  return { "meimg" };
}
