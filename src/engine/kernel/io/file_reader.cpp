#include "file_reader.h"
#include <stdio.h>

me::file_state me::read_file(const std::string &filepath)
{
  FILE* file = fopen(filepath.c_str(), "rb");
  fseek(file, 0, SEEK_END);
  uint64_t file_size = ftell(file);
  rewind(file);
  unsigned char* buffer = new unsigned char[file_size];
  fread(buffer, file_size, 1, file);
  fclose(file);
  return me::file_state(filepath, me::file_access::ALL, 0, 0, buffer, file_size);
}

void me::write_file(const std::string &filepath, unsigned char* data, uint64_t off, uint64_t len)
{

}
