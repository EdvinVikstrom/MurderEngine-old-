#ifndef FILE_STATE_H
  #define FILE_STATE_H

#include "../kernel.h"

namespace me {

  enum file_access {
    ALL,
    ADMIN,
    ROOT
  };

  struct file_state {
    std::string filepath;
    file_access access;
    long created, modified;

    unsigned char* data;
    unsigned int length;

    file_state(std::string filepath, me::file_access access, long created, long modified, unsigned char* data, unsigned int length)
    {
      this->filepath = filepath;
      this->access = access;
      this->created = created;
      this->modified = modified;
      this->data = data;
      this->length = length;
    }

    file_state(std::string filepath, me::file_access access, long created, long modified)
    {
      file_state(filepath, access, created, modified, nullptr, 0);
    }

    ~file_state()
    {
      delete[] data;
    }

  };

};

#endif
