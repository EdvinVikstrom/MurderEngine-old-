#ifndef BYTE_BUFFER_H
  #define BYTE_BUFFER_H

#include "../kernel.h"

namespace me {

  struct byte_buffer { // TODO: Not done!!!

    unsigned char* bytes;
    unsigned int length, pos;

    byte_buffer(unsigned char* bytes, unsigned int length)
    {
      this->bytes = bytes;
      this->length = length;
      pos = 0;
    }

    inline int16_t int16()
    {
      int16_t o = uint16_t(
        (bytes[pos+1]) << 8 |
        (bytes[pos]));
      pos+=sizeof(int16_t);
      return o;
    }

    inline int32_t int32()
    {
      int32_t o = uint32_t(
        (bytes[pos+3]) << 24 |
        (bytes[pos+2]) << 16 |
        (bytes[pos+1]) << 8 |
        (bytes[pos]));
      pos+=sizeof(int32_t);
      return o;
    }

    inline uint16_t uint16()
    {
      uint16_t o = uint16_t(
        (bytes[pos+1]) << 8 |
        (bytes[pos]));
      pos+=sizeof(uint16_t);
      return o;
    }

    inline uint32_t uint32()
    {
      uint32_t o = uint32_t(
        (bytes[pos+3]) << 24 |
        (bytes[pos+2]) << 16 |
        (bytes[pos+1]) << 8 |
        (bytes[pos]));
      pos+=sizeof(uint32_t);
      return o;
    }

    inline void reset()
    {
      pos = 0;
    }

  };

};

#endif
