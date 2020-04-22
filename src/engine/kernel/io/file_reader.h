#ifndef FILE_READER_H
  #define FILE_READER_H

#include "../kernel.h"

namespace me {

  struct filebuff {

    unsigned char* data;
    uint64_t length, pos;

    filebuff(unsigned char* data, uint64_t length)
    {
      this->data = data;
      this->length = length;
      pos = 0;
    }

    filebuff()
    {
      length = 0;
      pos = 0;
    }

    ~filebuff()
    {
      #ifdef ME_DEBUG
        printf("file buffer destroyed / length: %ld\n", length);
      #endif
    }

    inline unsigned char* atPos(uint32_t size)
    {
      return &data[pos+=size];
    }

    inline unsigned char read()
    {
      return data[pos++];
    }

    inline short _short()
    {
      short o = short(
        (data[pos+1]) << 8 |
        (data[pos])
      );
      pos+=2;
      return o;
    }

    inline int _int()
    {
      int o = int(
        (data[pos+3]) << 24 |
        (data[pos+2]) << 16 |
        (data[pos+1]) << 8 |
        (data[pos])
      );
      pos+=4;
      return o;
    }

    inline long _long()
    {
      long o = long(
        (long)(data[pos+7]) << 56L |
        (long)(data[pos+6]) << 48L |
        (long)(data[pos+5]) << 40L |
        (long)(data[pos+4]) << 32L |
        (long)(data[pos+3]) << 24L |
        (long)(data[pos+2]) << 16L |
        (long)(data[pos+1]) << 8L |
        (long)(data[pos+=8])
      );
      pos+=8;
      return o;
    }

    inline uint16_t _uint16()
    {
      uint16_t o = uint16_t(
        (data[pos+1]) << 8 |
        (data[pos])
      );
      pos+=2;
      return o;
    }

    inline uint32_t _uint32()
    {
      uint32_t o = uint32_t(
        (data[pos+3]) << 24 |
        (data[pos+2]) << 16 |
        (data[pos+1]) << 8 |
        (data[pos])
      );
      pos+=4;
      return o;
    }

    inline uint64_t _uint64()
    {
      uint64_t o = uint64_t(
        (long)(data[pos+7]) << 56L |
        (long)(data[pos+6]) << 48L |
        (long)(data[pos+5]) << 40L |
        (long)(data[pos+4]) << 32L |
        (long)(data[pos+3]) << 24L |
        (long)(data[pos+2]) << 16L |
        (long)(data[pos+1]) << 8L |
        (long)(data[pos])
      );
      pos+=8;
      return o;
    }

    inline float _float() // TODO:
    {
      return float(
        (data[pos++]) << 24 |
        (data[pos++]) << 16 |
        (data[pos++]) << 8 |
        (data[pos++])
      );
    }

    inline double _double() // TODO:
    {
      return double(
        (long)(data[pos++]) << 56L |
        (long)(data[pos++]) << 48L |
        (long)(data[pos++]) << 40L |
        (long)(data[pos++]) << 32L |
        (long)(data[pos++]) << 24L |
        (long)(data[pos++]) << 16L |
        (long)(data[pos++]) << 8L |
        (long)(data[pos++])
      );
    }

    inline void reset()
    {
      pos = 0;
    }

    inline void flush()
    {
      delete[] data;
      #ifdef ME_DEBUG
        printf("file buffer flushed / length: %ld\n", length);
      #endif
      length = 0;
      pos = 0;
    }

  };

  enum file_access {
    ALL,
    ADMIN,
    ROOT
  };

  /* it looks cooler */
  struct fileattr {
    const char* filepath;
    file_access access;
    long created, modified;
    FILE* file;

    me::filebuff* buffer;

    fileattr(const char* filepath, file_access access, long created, long modified, FILE* file, me::filebuff* buffer)
    {
      this->filepath = filepath;
      this->access = access;
      this->created = created;
      this->modified = modified;
      this->file = file;
      this->buffer = buffer;
    }

    ~fileattr()
    {
      delete file;
      delete buffer;
    }

    void readFile();
    void closeFile();

  };

  me::fileattr* load_file(const char* filepath);
  void write_file(const char* filepath, unsigned char* data, uint64_t off, uint64_t len);
  int cleanup_buffers();

};

#endif
