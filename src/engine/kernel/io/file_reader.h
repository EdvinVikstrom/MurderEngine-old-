#ifndef FILE_READER_H
  #define FILE_READER_H

#include "../kernel.h"

namespace me {

  enum ByteOrder : unsigned char {
    BO_BIG_ENDIAN = 0,
    BO_LITTLE_ENDIAN = 1
  };

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

    inline uint32_t remaining()
    {
      return length - pos;
    }

    inline bool hasRemaining()
    {
      return pos < length;
    }

    inline unsigned char* atPos(uint32_t size)
    {
      return &data[pos+=size];
    }

    inline unsigned char read()
    {
      return data[pos++];
    }

    inline unsigned char* read(uint32_t length)
    {
      unsigned char* output = new unsigned char[length];
      for (uint32_t i = 0; i < length; i++)
      {
        output[i] = data[pos];
        pos++;
      }
      return output;
    }

    inline short _short()
    {
      short o = short((data[pos+1]) << 8 | (data[pos]));
      pos+=2;
      return o;
    }

    inline int _int()
    {
      int o = int((data[pos+3]) << 24 | (data[pos+2]) << 16 | (data[pos+1]) << 8 | (data[pos]));
      pos+=4;
      return o;
    }

    inline long _long()
    {
      long o = long(
        (long)(data[pos+7]) << 56L | (long)(data[pos+6]) << 48L | (long)(data[pos+5]) << 40L | (long)(data[pos+4]) << 32L |
        (long)(data[pos+3]) << 24L | (long)(data[pos+2]) << 16L | (long)(data[pos+1]) << 8L | (long)(data[pos+=8]));
      pos+=8;
      return o;
    }

    inline uint16_t _uint16()
    {
      uint16_t o = uint16_t((data[pos+1]) << 8 | (data[pos]));
      pos+=2;
      return o;
    }

    inline uint32_t _uint32()
    {
      uint32_t o = uint32_t((data[pos+3]) << 24 | (data[pos+2]) << 16 | (data[pos+1]) << 8 | (data[pos]));
      pos+=4;
      return o;
    }

    inline uint64_t _uint64()
    {
      uint64_t o = uint64_t(
        (long)(data[pos+7]) << 56L | (long)(data[pos+6]) << 48L | (long)(data[pos+5]) << 40L | (long)(data[pos+4]) << 32L |
        (long)(data[pos+3]) << 24L | (long)(data[pos+2]) << 16L | (long)(data[pos+1]) << 8L | (long)(data[pos]));
      pos+=8;
      return o;
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

  struct write_buffer {

    std::vector<unsigned char> bytes;
    me::ByteOrder byte_order = BO_BIG_ENDIAN;

    write_buffer(std::vector<unsigned char> bytes, me::ByteOrder byte_order)
    {
      this->bytes = bytes;
      this->byte_order = byte_order;
    }

    write_buffer(me::ByteOrder byte_order)
    {
      this->byte_order = byte_order;
    }

    write_buffer() { }

    ~write_buffer()
    {
      bytes.clear();
    }

    inline void order(me::ByteOrder byte_order)
    {
      this->byte_order = byte_order;
    }

    inline uint32_t length()
    {
      return bytes.size();
    }

    inline void push_mem(uint32_t mem)
    {
      bytes.reserve(bytes.size() + mem);
    }

    inline unsigned char& at(uint32_t index)
    {
      return bytes.at(index);
    }

    inline void push(unsigned char byte)
    {
      bytes.emplace_back(byte);
    }

    inline void push(const char* string)
    {
      uint32_t str_length = strlen(string);
      bytes.reserve(bytes.size() + str_length);
      for (uint32_t i = 0; i < str_length; i++)
        bytes.push_back((unsigned char) string[i]);
    }

    inline void push_int16(short i)
    {
      for (unsigned char j = 0; j < 2; j++)
        bytes.push_back((i >> ((byte_order == BO_LITTLE_ENDIAN ? j : 1 - j) * 8)) & 0xFF);
    }

    inline void push_int32(int i)
    {
      for (unsigned char j = 0; j < 4; j++)
        bytes.push_back((i >> ((byte_order == BO_LITTLE_ENDIAN ? j : 3 - j) * 8)) & 0xFF);
    }

    inline void push_int64(long i)
    {
      for (unsigned char j = 0; j < 8; j++)
        bytes.push_back((i >> ((byte_order == BO_LITTLE_ENDIAN ? j : 7 - j) * 8)) & 0xFF);
    }

    inline void push_uint16(uint16_t i)
    {
      for (unsigned char j = 0; j < 2; j++)
        bytes.push_back((i >> ((byte_order == BO_LITTLE_ENDIAN ? j : 1 - j) * 8)) & 0xFF);
    }

    inline void push_uint32(uint32_t i)
    {
      for (unsigned char j = 0; j < 4; j++)
        bytes.push_back((i >> ((byte_order == BO_LITTLE_ENDIAN ? j : 3 - j) * 8)) & 0xFF);
    }

    inline void push_uint64(uint64_t i)
    {
      for (unsigned char j = 0; j < 8; j++)
        bytes.push_back((i >> ((byte_order == BO_LITTLE_ENDIAN ? j : 7 - j) * 8)) & 0xFF);
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
