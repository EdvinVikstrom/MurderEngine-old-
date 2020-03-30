#include "file_reader.h"
#include <stdio.h>

unsigned char* me::read_file(const std::string &filepath, uint64_t &file_size)
{
  FILE* file = fopen(filepath, "rb");
  fseek(file, 0, SEEK_END);
  file_size = ftell(file);
  rewind(file);
  unsigned char* buffer = new unsigned char[file_size];
  fread(buffer, file_size, 1, file);
  fclose(file);
  return buffer;
}

void me::write_file(const std::string &filepath, unsigned char* data, uint64_t off, uint64_t len)
{

}
