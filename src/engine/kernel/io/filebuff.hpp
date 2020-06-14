#ifndef FILEBUFF_HPP
  #define FILEBUFF_HPP

#include "../common.hpp"
#include "bytebuff.hpp"

namespace me {

  enum file_access {
    ALL,
    ROOT
  };

  struct filebuff {
    std::string filepath;
    file_access access;
    long created, modified;
    FILE* file;

    me::bytebuff* buffer;

    filebuff(std::string filepath, file_access access, long created, long modified, FILE* file, me::bytebuff* buffer)
    {
      this->filepath = filepath;
      this->access = access;
      this->created = created;
      this->modified = modified;
      this->file = file;
      this->buffer = buffer;
    }

    ~filebuff()
    {
      delete file;
      delete buffer;
    }

    filebuff* readFile();
    filebuff* closeFile();

  };

  me::filebuff* loadFile(const std::string &filepath);
  void writeFile(const std::string &filepath, unsigned char* data, uint64_t off, uint64_t len);

};

#endif
