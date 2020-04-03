#ifndef FILE_READER_H
  #define FILE_READER_H

#include "../kernel.h"
#include "file_state.h"

namespace me {

  me::file_state read_file(const std::string &filepath);
  void write_file(const std::string &filepath, unsigned char* data, uint64_t off, uint64_t len);

  inline bool is_abs_path(std::string &filepath)
  {
    return filepath.at(0)=='/' || filepath.at(0)=='\\' || filepath.at(1)==':';
  }

};

#endif
