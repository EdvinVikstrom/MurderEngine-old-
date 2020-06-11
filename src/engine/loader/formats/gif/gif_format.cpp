#include "gif_format.hpp"

int me::format::gif_format::load_image(me::bytebuff &buffer, me::Image* image, uint64_t flags)
{
  /*
  file.readFile();
  gif_header header;
  header.signature = new unsigned char[6] {
    file.buffer->pull(), file.buffer->pull(), file.buffer->pull(),
    file.buffer->pull(), file.buffer->pull(), file.buffer->pull()
  };

  header.width = file.buffer->pull_uint16();
  header.height = file.buffer->pull_uint16();
  header.packedFields = file.buffer->pull();

  header.globalColorTableFlag = (header.packedFields & 128) != 0;
  header.colorResolution = (header.packedFields >> 4 & 7) + 1;
  header.sortFlag = (header.packedFields & 8) != 0;
  header.nGCTEntries = 1 << (header.packedFields & 7) + 1;

  header.bgColorIndex = file.buffer->pull();
  header.pixelAspectRatio = file.buffer->pull();
  */
  return ME_FINE;
}

int me::format::gif_format::write_image(me::bytebuff &buffer, me::Image* image, uint64_t flags)
{
  return ME_FINE;
}

bool me::format::gif_format::recognized(me::fileattr &file)
{
  return me::str_ends(file.filepath, ".gif");
}

std::vector<std::string> me::format::gif_format::get_file_exts()
{
  return { "gif" };
}

uint64_t me::format::gif_format::supported_flags()
{
  return 0; // TODO:
}