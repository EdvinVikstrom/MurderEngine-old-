#include "ico_format.hpp"

int me::format::ico_format::next_entry(me::bytebuff &buffer, ico_dir_entry &entry)
{
  if (!buffer.canPull(sizeof(ico_dir_entry)))
  return ME_ERR;
  entry.imageWidth = buffer.pull();
  entry.imageHeight = buffer.pull();
  entry.nColors = buffer.pull();
  entry.reserved = buffer.pull();
  entry.offset = buffer.pull_uint16();
  entry.bitsPerPixel = buffer.pull_uint16();
  entry.imageSize = buffer.pull_uint32();
  entry.offset = buffer.pull_uint32();
  return ME_FINE;
}

int me::format::ico_format::read_header(me::bytebuff &buffer, ico_header &header)
{
  if (!buffer.canPull(sizeof(ico_header))) // yes i know, the header contains a pointer
  return ME_ERR;
  header.reserved = buffer.pull_uint16();
  header.type = buffer.pull_uint16();
  header.nImages = buffer.pull_uint16();
  header.entries = new ico_dir_entry[header.nImages];
  for (uint16_t i = 0; i < header.nImages; i++)
  {
    if (next_entry(buffer, header.entries[i]) != ME_FINE)
    {
      std::cout << "[ICOLoader] [ERR]: failed to read ico dir entry\n";
      return ME_ERR;
    }
  }
  return ME_FINE;
}

int me::format::ico_format::load_image(me::bytebuff &buffer, me::Image* image, uint64_t flags)
{
  buffer.byteOrder(me::ByteOrder::BO_BIG_ENDIAN);
  ico_header header;
  if (read_header(buffer, header) != ME_FINE)
  {
    std::cout << "[ICOLoader] [ERR]: failed to read ico header\n";
    return ME_ERR;
  }
  for (uint32_t i = 0; i < header.nImages; i++)
  {
    ico_dir_entry &entry = header.entries[i];
    buffer.jump(entry.offset);
    std::cout << "FORMAT: " << (uint16_t) buffer.pull();
    std::cout << (uint16_t) buffer.pull() << "\n";
  }
  return ME_FINE;
}

int me::format::ico_format::write_image(me::bytebuff &buffer, me::Image* image, uint64_t flags)
{
  ico_header header;
  header.reserved = 0;
  header.type = 0;
  header.nImages = 1;
  buffer.byteOrder(me::ByteOrder::BO_LITTLE_ENDIAN);
  buffer.push_uint16(header.reserved);
  buffer.push_uint16(header.type);
  buffer.push_uint16(header.nImages);
  return ME_FINE;
}

bool me::format::ico_format::recognized(me::fileattr &file)
{
  return me::str_ends(file.filepath, ".ico") || me::str_ends(file.filepath, ".cur");
}

std::vector<std::string> me::format::ico_format::get_file_exts()
{
  return { "ico", "cur" };
}

uint64_t me::format::ico_format::supported_flags()
{
  return 0; // TODO:
}
