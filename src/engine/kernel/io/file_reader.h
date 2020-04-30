#ifndef FILE_READER_H
  #define FILE_READER_H

#include "../kernel.h"
#include <map>

namespace me {

  enum ByteOrder : unsigned char {
    BO_BIG_ENDIAN = 0,
    BO_LITTLE_ENDIAN = 1
  };

  enum BitOrder : unsigned char {
    BO_FIRST = 0,
    BO_LAST = 1,
  };

  enum ByteBuffMode {
    BBMODE_READ,
    BBMODE_WRITE
  };

  struct bitbuff {
    std::vector<unsigned char> data;
    uint32_t length, pos;

    void push(uint8_t i);
    void push_uint(uint64_t i, uint32_t length);

  };

  struct bytebuff {
    std::string source;
    std::vector<unsigned char> data;
    uint64_t length, pos, bit_pos;
    me::ByteOrder byte_order;
    me::BitOrder bit_order;
    me::ByteBuffMode mode;

    bytebuff(std::string source, uint64_t length, ByteOrder byte_order, BitOrder bit_order, me::ByteBuffMode mode)
    {
      this->source = source;
      this->length = length;
      pos = 0;
      bit_pos = 0;
      this->byte_order = byte_order;
      this->bit_order = bit_order;
      this->mode = mode;
    }

    bytebuff()
    {
      source = "unknown";
      length = 0;
      pos = 0;
      bit_pos = 0;
      byte_order = BO_BIG_ENDIAN;
      bit_order = BO_LAST;
      mode = BBMODE_WRITE;
    }

    static uint16_t to_uint16(uint8_t* bytes, uint32_t offset, me::ByteOrder order);
    static uint32_t to_uint24(uint8_t* bytes, uint32_t offset, me::ByteOrder order);
    static uint32_t to_uint32(uint8_t* bytes, uint32_t offset, me::ByteOrder order);
    static uint64_t to_uint64(uint8_t* bytes, uint32_t offset, me::ByteOrder order);

    static uint8_t* from_uint16(uint8_t* dest, uint16_t i, me::ByteOrder order);
    static uint8_t* from_uint24(uint8_t* dest, uint32_t i, me::ByteOrder order);
    static uint8_t* from_uint32(uint8_t* dest, uint32_t i, me::ByteOrder order);
    static uint8_t* from_uint64(uint8_t* dest, uint64_t i, me::ByteOrder order);

    static uint16_t to_uint16(uint8_t* bytes, me::ByteOrder order);
    static uint32_t to_uint24(uint8_t* bytes, me::ByteOrder order);
    static uint32_t to_uint32(uint8_t* bytes, me::ByteOrder order);
    static uint64_t to_uint64(uint8_t* bytes, me::ByteOrder order);

    void byteOrder(me::ByteOrder order);
    void bitOrder(me::BitOrder order);

    void pushMem(uint64_t mem);
    void flip();
    bool hasRemaining();
    bool canPull(uint32_t length);
    uint64_t remaining();
    void skip(uint32_t nBytes);
    void jump(uint64_t index);

    uint8_t pull();
    uint8_t* pull(uint8_t* bytes, uint32_t length);
    uint16_t pull_uint16();
    uint32_t pull_uint24();
    uint32_t pull_uint32();
    uint64_t pull_uint64();
    uint64_t pull_uint(uint32_t bits);

    uint16_t pull_bits(uint16_t bit_length);

    void push(unsigned char byte);
    void push(unsigned char* data, uint32_t length);
    void push_uint16(uint16_t i);
    void push_uint24(uint32_t i);
    void push_uint32(uint32_t i);
    void push_uint64(uint64_t i);

    void push_bits(uint32_t i, uint16_t bit_length);

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

  struct Archive {
    std::map<std::string, me::fileattr*> files;
  };

  me::fileattr* load_file(const char* filepath);
  void write_file(const char* filepath, unsigned char* data, uint64_t off, uint64_t len);
  int cleanup_buffers();

};

#endif
