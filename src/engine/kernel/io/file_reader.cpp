#include "file_reader.h"
#include <iostream>
#include <stdio.h>

static std::vector<me::filebuff*> buffers;

/* file preview buffer */
static uint32_t MINI_BUFFER_SIZE = 24;

/* read the first 24 bytes of a file so we can "recognize" the file */
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
  /* get the file size */
  fseek(file, 0, SEEK_END);
  uint64_t file_size = ftell(file);

  /* reset to file beginning */
  rewind(file);

  /* allocate memory */
  uint32_t size = file_size < MINI_BUFFER_SIZE ? file_size : MINI_BUFFER_SIZE;
  char* data = new char[size];

  /* read to memory */
  fread(data, size, 1, file);

  /* reset */
  rewind(file);

  /* create file buffer with the file size and data */
  me::filebuff* buffer = new me::filebuff((unsigned char*)data, file_size);
  buffers.push_back(buffer);
  return new me::fileattr(filepath, file_access::ALL, 0L, 0L, file, buffer);
}

void me::write_file(const char* filepath, unsigned char* data, uint64_t off, uint64_t len)
{

}

/* read the full file from filebuff */
void me::fileattr::readFile()
{
  /* allocate new memory to filebuff */
  char* data = new char[buffer->length];

  /* read to memory */
  fread(data, buffer->length, 1, file);

  /* close the file and update filebuff */
  fclose(file);
  buffer->data = (unsigned char*) data;
}

/* close the filebuff */
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
