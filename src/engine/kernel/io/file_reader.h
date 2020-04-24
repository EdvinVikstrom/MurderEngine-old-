#ifndef FILE_READER_H
  #define FILE_READER_H

#include "../kernel.h"

namespace me {

  enum ByteOrder : unsigned char {
    BO_BIG_ENDIAN = 0,
    BO_LITTLE_ENDIAN = 1
  };

  enum BitOrder : unsigned char {
    BO_FIRST = 0,
    BO_LAST = 1,
  };

  struct bytebuff {
    std::vector<unsigned char> data;
    uint64_t length, pos, bit_pos;
    me::ByteOrder byte_order;
    me::BitOrder bit_order;

    bytebuff(uint64_t length, ByteOrder byte_order, BitOrder bit_order)
    {
      this->length = length;
      pos = 0;
      bit_pos = 0;
      this->byte_order = byte_order;
      this->bit_order = bit_order;
    }

    bytebuff()
    {
      length = 0;
      pos = 0;
      bit_pos = 0;
      byte_order = BO_BIG_ENDIAN;
      bit_order = BO_LAST;
    }

    void byteOrder(me::ByteOrder order);
    void bitOrder(me::BitOrder order);

    void pushMem(uint64_t mem);
    void flip();
    bool hasRemaining();
    uint64_t remaining();
    uint8_t read();
    void write(unsigned char byte);

    uint8_t* read(uint64_t bit_length, uint64_t byte_length);
    void write(uint8_t* bytes, uint64_t bit_length, uint64_t byte_length);

    uint8_t pull();
    uint8_t* pull(uint32_t length);
    short pull_int16();
    int pull_int24();
    int pull_int32();
    long pull_int64();

    uint16_t pull_uint16();
    uint32_t pull_uint24();
    uint32_t pull_uint32();
    uint64_t pull_uint64();

    long pull_int(uint32_t bit_length);
    uint64_t pull_uint(uint32_t bit_length);

    void push(unsigned char byte);
    void push(unsigned char* data, uint32_t length);
    void push_int16(short i);
    void push_int24(int i);
    void push_int32(int i);
    void push_int64(long i);

    void push_uint16(uint16_t i);
    void push_uint24(uint32_t i);
    void push_uint32(uint32_t i);
    void push_uint64(uint64_t i);

    void push_int(long i, uint32_t bit_length);
    void push_uint(uint64_t i, uint32_t bit_length);

    void flush();

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

    me::bytebuff* buffer;

    fileattr(const char* filepath, file_access access, long created, long modified, FILE* file, me::bytebuff* buffer)
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
