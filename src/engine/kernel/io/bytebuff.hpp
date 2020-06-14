#ifndef BYTEBUFF_HPP
  #define BYTEBUFF_HPP

#include "../common.hpp"
#include <vector>

namespace me {

  enum ByteOrder : unsigned char {
    BO_BIG_ENDIAN = 0,
    BO_LITTLE_ENDIAN = 1
  };

  enum ByteBuffMode {
    BBMODE_READ,
    BBMODE_WRITE
  };

  struct bytebuff {
    std::string source;
    uint8_t* data;
    uint64_t length, pos;
    me::ByteOrder byte_order;
    me::ByteBuffMode mode;

    bytebuff(std::string source, uint8_t* data, uint64_t length, ByteOrder byte_order, me::ByteBuffMode mode)
    {
      this->source = source;
      this->data = data;
      this->length = length;
      this->byte_order = byte_order;
      this->mode = mode;
      pos = 0;
    }

    bytebuff(std::string source, uint64_t length, ByteOrder byte_order)
    {
      this->source = source;
      data = new uint8_t[length];
      this->length = length;
      this->byte_order = byte_order;
      this->mode = BBMODE_WRITE;
      pos = 0;
    }

    bytebuff()
    {
      source = "unknown";
      data = nullptr;
      length = 0;
      pos = 0;
      byte_order = BO_BIG_ENDIAN;
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

    void push(unsigned char byte);
    void push(unsigned char* data, uint32_t length);
    void push_uint16(uint16_t i);
    void push_uint24(uint32_t i);
    void push_uint32(uint32_t i);
    void push_uint64(uint64_t i);

    void flush();

  };

};

#endif
