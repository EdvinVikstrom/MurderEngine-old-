#include "file_reader.h"
#include <iostream>
#include <stdio.h>

static std::vector<me::filebuff*> buffers;
static uint32_t MINI_BUFFER_SIZE = 24;

me::fileattr* me::read_file(const char* filepath)
{
  FILE* file = fopen(filepath, "rb");
  #ifdef ME_DEBUG
    printf("reading file from \"%s\"\n", filepath);
  #endif
  if (file==nullptr)
  {
    std::cerr << "failed to read file \"" << filepath << "\"\n";
    return nullptr;
  }
  fseek(file, 0, SEEK_END);
  uint64_t file_size = ftell(file);
  rewind(file);

  uint32_t size = file_size < MINI_BUFFER_SIZE ? file_size : MINI_BUFFER_SIZE;
  char* data = new char[size];
  fread(data, size, 1, file);
  rewind(file);

  me::filebuff* buffer = new me::filebuff((unsigned char*)data, file_size);
  buffers.push_back(buffer);
  return new me::fileattr(filepath, file_access::ALL, 0L, 0L, file, buffer);
}

void me::write_file(const char* filepath, unsigned char* data, uint64_t off, uint64_t len)
{

}

void me::fileattr::readFile()
{
  char* data = new char[buffer->length];
  fread(data, buffer->length, 1, file);
  fclose(file);
  buffer->data = (unsigned char*) data;
}

void me::fileattr::closeFile()
{
  fclose(file);
}

int me::cleanup_buffers()
{
  int count = 0;
  for (me::filebuff* buffer : buffers)
  {
    if (buffer==nullptr)
      continue;
    delete buffer;
    count++;
  }
  return count;
}
