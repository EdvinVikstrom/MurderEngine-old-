#include "file_reader.h"
#include <stdio.h>
#include <iostream>

static std::vector<me::filebuff*> buffers;

me::fileattr* me::load_file(const char* filepath)
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
  /* get the file size */
  fseek(file, 0, SEEK_END);
  uint64_t file_size = ftell(file);
  rewind(file);

  me::filebuff* buffer = new me::filebuff(nullptr, file_size);
  buffers.push_back(buffer);
  return new me::fileattr(filepath, file_access::ALL, 0L, 0L, file, buffer);
}

void me::write_file(const char* filepath, unsigned char* data, uint64_t off, uint64_t len)
{
  FILE* file = fopen(filepath, "wb");
  fwrite(data, 1, len, file);
  fclose(file);
}

void me::fileattr::readFile()
{
  char* data = new char[buffer->length + 1];
  fread(data, buffer->length, 1, file);
  data[buffer->length] = 0;

  if (file != nullptr) fclose(file);
  buffer->data = (unsigned char*) data;
}

/* close the filebuff */
void me::fileattr::closeFile()
{
  if (file != nullptr) fclose(file);
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
