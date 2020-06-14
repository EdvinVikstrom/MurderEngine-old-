#include "zip_format.hpp"

int me::format::zip_format::next_file(me::bytebuff &buffer, zip_file &file)
{
  file.header.signature = buffer.pull_uint32();
  if (file.header.signature != 0x04034b50)
  return ME_FILE_WRONG_TYPE;
  file.header.minVersion = buffer.pull_uint16();
  file.header.flag = buffer.pull_uint16();
  file.header.compressionMethod = buffer.pull_uint16();
  file.header.lastModificationTime = buffer.pull_uint16();
  file.header.lastModificationDate = buffer.pull_uint16();
  file.header.CRC32 = buffer.pull_uint32();
  file.header.compressedSize = buffer.pull_uint32();
  file.header.uncompressedSize = buffer.pull_uint32();
  file.header.fileNameLength = buffer.pull_uint16();
  file.header.extraFieldLength = buffer.pull_uint16();
  file.header.fileName = buffer.pull(new uint8_t[file.header.fileNameLength], file.header.fileNameLength);
  file.header.extraField = buffer.pull(new uint8_t[file.header.extraFieldLength], file.header.extraFieldLength);
  file.data = buffer.pull(new uint8_t[file.header.compressedSize], file.header.compressedSize);
  for (uint32_t i = 0; i < file.header.compressedSize; i++)
  std::cout << file.data[i];
  std::cout << "\n\n";
  return ME_FINE;
}

int me::format::zip_format::load_archive(me::bytebuff &buffer, me::Archive* archive, uint64_t flags)
{
  buffer.byteOrder(me::ByteOrder::BO_BIG_ENDIAN);
  zip_struct zip;
  for (uint32_t i = 0; i < 1; i++)
  {
    zip_file* file = new zip_file;
    zip.files.push_back(file);
    next_file(buffer, *file);
    for (uint32_t i = 0; i < file->header.fileNameLength; i++)
    std::cout << file->header.fileName[i];
    std::cout << "\n";
  }
  return ME_FINE;
}

int me::format::zip_format::write_archive(me::bytebuff &buffer, me::Archive* archive, uint64_t flags)
{
  return ME_FINE;
}

bool me::format::zip_format::recognized(me::fileattr &file)
{
  return me::str_ends(file.filepath, ".zip");
}

std::vector<std::string> me::format::zip_format::get_file_exts()
{
  return { "zip" };
}

uint64_t me::format::zip_format::supported_flags()
{
  return 0; // TODO:
}
