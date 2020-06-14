#include "filebuff.hpp"
#include <stdio.h>
#include <iostream>

me::filebuff* me::loadFile(const std::string &filepath)
{
  FILE* file = fopen(filepath.c_str(), "rb");
  printf("loading file \"%s\"\n", filepath.c_str());
  if (file==nullptr)
  {
    printf("failed to load file \"%s\"\n", filepath.c_str());
    return nullptr;
  }
  /* get the file size */
  fseek(file, 0, SEEK_END);
  uint64_t file_size = ftell(file);
  rewind(file);

  me::bytebuff* buffer = new me::bytebuff(filepath, new uint8_t[file_size + 1], file_size, me::ByteOrder::BO_BIG_ENDIAN, me::ByteBuffMode::BBMODE_READ);
  buffer->data[file_size] = 0;
  return new me::filebuff(filepath, file_access::ALL, 0L, 0L, file, buffer);
}

void me::writeFile(const std::string &filepath, unsigned char* data, uint64_t off, uint64_t len)
{
  FILE* file = fopen(filepath.c_str(), "wb");
  fwrite(data, 1, len, file);
  fclose(file);
}

me::filebuff* me::filebuff::readFile()
{
  // printf("reading file \"%s\"\n", filepath.c_str());
  fread(&buffer->data[0], buffer->length, 1, file);
  return closeFile();
}

/* close the filebuff */
me::filebuff* me::filebuff::closeFile()
{
  if (file != nullptr)
  fclose(file);
  return this;
}
