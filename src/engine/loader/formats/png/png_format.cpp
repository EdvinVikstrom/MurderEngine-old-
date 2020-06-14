#include "png_format.hpp"
#include "../../../../external/libpng/png.hpp"

int me::format::png_format::read_header(me::bytebuff &buffer, png_header &header)
{
  header.signature = buffer.pull(new uint8_t[8], 8);
  if (
  header.signature[0] == 0x89 &&
  header.signature[1] == 0x50 &&
  header.signature[2] == 0x4E &&
  header.signature[3] == 0x47 &&
  header.signature[4] == 0x0D &&
  header.signature[5] == 0x0A &&
  header.signature[6] == 0x1A &&
  header.signature[7] == 0x0A)
  return ME_FINE;
  return ME_FILE_WRONG_TYPE;
}

int me::format::png_format::next_chunk(me::bytebuff &buffer, png_chunk* chunk)
{
  chunk->length = buffer.pull_uint32();
  chunk->type = buffer.pull_uint32();
  chunk->data = buffer.pull(new uint8_t[chunk->length], chunk->length);
  chunk->crc = buffer.pull_uint32();
  return ME_FINE;
}

int me::format::png_format::read_chunks(me::bytebuff &buffer, std::map<uint32_t, png_chunk*> &chunks)
{
  //while(buffer.hasRemaining())
  //{
    png_chunk* chunk = new png_chunk;
    next_chunk(buffer, chunk);
    chunks[chunk->type] = chunk;
  //}
  return ME_FINE;
}

int me::format::png_format::load_image(me::bytebuff &buffer, me::Image* image, uint64_t flags)
{
  buffer.byteOrder(me::ByteOrder::BO_LITTLE_ENDIAN);
  png_struct png;
  read_header(buffer, png.header);
  read_chunks(buffer, png.chunks);
  png_chunk_hdri hdri(*png.chunks[PNG_CHUNK_IHDR]);
  std::cout << "[PNGLoader] [IMAGE INFO]: width: " << hdri.width << ", height: " << hdri.height << "\n";
  return ME_FINE;
}

int me::format::png_format::write_image(me::bytebuff &buffer, me::Image* image, uint64_t flags)
{
  return ME_FINE;
}

bool me::format::png_format::recognized(me::fileattr &file)
{
  return me::str_ends(file.filepath, ".png");
}

std::vector<std::string> me::format::png_format::get_file_exts()
{
  return { "png" };
}

uint64_t me::format::png_format::supported_flags()
{
  return 0; // TODO:
}
