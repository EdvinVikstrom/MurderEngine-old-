#ifndef FILE_READER_H
  #define FILE_READER_H

#include "../kernel.h"

namespace me {

  unsigned char* read_file(const std::string &filepath, uint64_t &file_size);
  void write_file(const std::string &filepath, unsigned char* data, uint64_t off, uint64_t len);

};

#endif
