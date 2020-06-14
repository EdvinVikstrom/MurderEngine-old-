/* *THIS CLASS CAN BE VERY CONFUSING */

#include "bytebuff.hpp"
#include "../../math/maths.hpp"

static uint8_t* to_bit_array(uint8_t* bytes, uint8_t offset, uint32_t length)
{
  uint64_t count = 1;
  uint8_t* bits = new uint8_t[length];
  for (uint32_t i = offset; i < length + offset; i++)
  {
    bits[i - offset] = ((bytes[i / 8] & count) > 0 ? 1 : 0);
    count*=2;
  }
  return bits;
}

uint16_t me::bytebuff::to_uint16(uint8_t* bytes, uint32_t offset, me::ByteOrder order)
{
  if (order == me::ByteOrder::BO_LITTLE_ENDIAN) return (uint16_t) {
    (bytes[offset + 0] << 8) |
    (bytes[offset + 1])
  };
  else return (uint16_t) {
    (bytes[offset + 1] << 8) |
    (bytes[offset + 0])
  };
}
uint32_t me::bytebuff::to_uint24(uint8_t* bytes, uint32_t offset, me::ByteOrder order)
{
  if (order == me::ByteOrder::BO_LITTLE_ENDIAN) return (uint32_t) {
    (bytes[offset + 0] << 16) |
    (bytes[offset + 1] << 8) |
    (bytes[offset + 2])
  };
  else return (uint32_t) {
    (bytes[offset + 2] << 16) |
    (bytes[offset + 1] << 8) |
    (bytes[offset + 0])
  };
}
uint32_t me::bytebuff::to_uint32(uint8_t* bytes, uint32_t offset, me::ByteOrder order)
{
  if (order == me::ByteOrder::BO_LITTLE_ENDIAN) return (uint32_t) {
    (bytes[offset + 0] << 24) |
    (bytes[offset + 1] << 16) |
    (bytes[offset + 2] << 8) |
    (bytes[offset + 3])
  };
  else return (uint32_t) {
    (bytes[offset + 3] << 24) |
    (bytes[offset + 2] << 16) |
    (bytes[offset + 1] << 8) |
    (bytes[offset + 0])
  };
}
uint64_t me::bytebuff::to_uint64(uint8_t* bytes, uint32_t offset, me::ByteOrder order)
{
  if (order == me::ByteOrder::BO_LITTLE_ENDIAN) return (uint64_t) {
    (bytes[offset + 0] << 56L) |
    (bytes[offset + 1] << 48L) |
    (bytes[offset + 2] << 40L) |
    (bytes[offset + 3] << 32L) |
    (bytes[offset + 4] << 24L) |
    (bytes[offset + 5] << 16L) |
    (bytes[offset + 6] << 8L) |
    (bytes[offset + 7])
  };
  else return (uint64_t) {
    (bytes[offset + 7] << 56L) |
    (bytes[offset + 6] << 48L) |
    (bytes[offset + 5] << 40L) |
    (bytes[offset + 4] << 32L) |
    (bytes[offset + 3] << 24L) |
    (bytes[offset + 2] << 16L) |
    (bytes[offset + 1] << 8L) |
    (bytes[offset + 0])
  };
}

uint8_t* me::bytebuff::from_uint16(uint8_t* dest, uint16_t i, me::ByteOrder order)
{
  if (order == me::ByteOrder::BO_LITTLE_ENDIAN)
  {
    dest[0] = (i >> 8) & 0xFF;
    dest[1] = i & 0xFF;
  }else
  {
    dest[1] = (i >> 8) & 0xFF;
    dest[0] = i & 0xFF;
  }
  return dest;
}
uint8_t* me::bytebuff::from_uint24(uint8_t* dest, uint32_t i, me::ByteOrder order)
{
  if (order == me::ByteOrder::BO_LITTLE_ENDIAN)
  {
    dest[0] = (i >> 16) & 0xFF;
    dest[1] = (i >> 8) & 0xFF;
    dest[2] = i & 0xFF;
  }else
  {
    dest[2] = (i >> 16) & 0xFF;
    dest[1] = (i >> 8) & 0xFF;
    dest[0] = i & 0xFF;
  }
  return dest;
}
uint8_t* me::bytebuff::from_uint32(uint8_t* dest, uint32_t i, me::ByteOrder order)
{
  if (order == me::ByteOrder::BO_LITTLE_ENDIAN)
  {
    dest[0] = (i >> 24) & 0xFF;
    dest[1] = (i >> 16) & 0xFF;
    dest[2] = (i >> 8) & 0xFF;
    dest[3] = i & 0xFF;
  }else
  {
    dest[3] = (i >> 24) & 0xFF;
    dest[2] = (i >> 16) & 0xFF;
    dest[1] = (i >> 8) & 0xFF;
    dest[0] = i & 0xFF;
  }
  return dest;
}
uint8_t* me::bytebuff::from_uint64(uint8_t* dest, uint64_t i, me::ByteOrder order)
{
  if (order == me::ByteOrder::BO_LITTLE_ENDIAN)
  {
    dest[0] = (i >> 56L) & 0xFF;
    dest[1] = (i >> 48L) & 0xFF;
    dest[2] = (i >> 40L) & 0xFF;
    dest[3] = (i >> 32L) & 0xFF;
    dest[4] = (i >> 24L) & 0xFF;
    dest[5] = (i >> 16L) & 0xFF;
    dest[6] = (i >> 8L) & 0xFF;
    dest[7] = i & 0xFF;
  }else
  {
    dest[7] = (i >> 56L) & 0xFF;
    dest[6] = (i >> 48L) & 0xFF;
    dest[5] = (i >> 40L) & 0xFF;
    dest[4] = (i >> 32L) & 0xFF;
    dest[3] = (i >> 24L) & 0xFF;
    dest[2] = (i >> 16L) & 0xFF;
    dest[1] = (i >> 8L) & 0xFF;
    dest[0] = i & 0xFF;
  }
  return dest;
}

uint16_t me::bytebuff::to_uint16(uint8_t* bytes, me::ByteOrder order)
{
  return to_uint16(bytes, 0, order);
}
uint32_t me::bytebuff::to_uint24(uint8_t* bytes, me::ByteOrder order)
{
  return to_uint24(bytes, 0, order);
}
uint32_t me::bytebuff::to_uint32(uint8_t* bytes, me::ByteOrder order)
{
  return to_uint32(bytes, 0, order);
}
uint64_t me::bytebuff::to_uint64(uint8_t* bytes, me::ByteOrder order)
{
  return to_uint64(bytes, 0, order);
}

void me::bytebuff::byteOrder(me::ByteOrder order)
{
  byte_order = order;
}

void me::bytebuff::flip()
{
  pos != 0 ? 0 : length - 1;
}
bool me::bytebuff::hasRemaining()
{
  return pos < length;
}
bool me::bytebuff::canPull(uint32_t length)
{
  return pos + length < this->length;
}
uint64_t me::bytebuff::remaining()
{
  return length - pos;
}
void me::bytebuff::skip(uint32_t nBytes)
{
  pos+=nBytes;
}
void me::bytebuff::jump(uint64_t index)
{
  pos = index;
}

unsigned char me::bytebuff::pull()
{
  pos++;
  return data[pos - 1];
}
uint8_t* me::bytebuff::pull(uint8_t* bytes, uint32_t length)
{
  for (uint32_t i = 0; i < length; i++)
  bytes[i] = data[pos++];
  return bytes;
}
uint16_t me::bytebuff::pull_uint16()
{
  uint16_t i = 0;
  if (byte_order == me::ByteOrder::BO_LITTLE_ENDIAN) i = (data[pos++] << 8) | (data[pos++]);
  else i = (data[pos++]) | (data[pos++] << 8);
  return i;
}
uint32_t me::bytebuff::pull_uint24()
{
  uint32_t i = 0;
  if (byte_order == me::ByteOrder::BO_LITTLE_ENDIAN) i = (data[pos++] << 16) | (data[pos++] << 8) | (data[pos++]);
  else i = (data[pos++]) | (data[pos++] << 8) | (data[pos++] << 16);
  return i;
}
uint32_t me::bytebuff::pull_uint32()
{
  uint32_t i = 0;
  if (byte_order == me::ByteOrder::BO_LITTLE_ENDIAN) i = (data[pos++] << 24) | (data[pos++] << 16) | (data[pos++] << 8) | (data[pos++]);
  else i = (data[pos++]) | (data[pos++] << 8) | (data[pos++] << 16) | (data[pos++] << 24);
  return i;
}
uint64_t me::bytebuff::pull_uint64()
{
  uint64_t i = 0;
  if (byte_order == me::ByteOrder::BO_LITTLE_ENDIAN) i = (data[pos++] << 56L) | (data[pos++] << 48L) | (data[pos++] << 40L) | (data[pos++] << 32L) | (data[pos++] << 24L) | (data[pos++] << 16L) | (data[pos++] << 8L) | (data[pos++]);
  else i = (data[pos++]) | (data[pos++] << 8L) | (data[pos++] << 16L) | (data[pos++] << 24L) | (data[pos++] << 32L) | (data[pos++] << 40L) | (data[pos++] << 48L) | (data[pos++] << 56L);
  return i;
}

void me::bytebuff::push(unsigned char byte)
{
  data[pos] = byte;
}
void me::bytebuff::push(unsigned char* data, uint32_t length)
{
  for (uint32_t i = 0; i < length; i++)
    this->data[pos + i] = data[i];
}
void me::bytebuff::push_uint16(uint16_t i)
{
  uint8_t* bytes = from_uint16(new uint8_t[2], i, byte_order);
  for (uint8_t j = 0; j < sizeof(uint16_t); j++)
    this->data[pos + j] = data[j];
}
void me::bytebuff::push_uint24(uint32_t i)
{
  uint8_t* bytes = from_uint24(new uint8_t[3], i, byte_order);
  for (uint8_t j = 0; j < 3; j++)
    this->data[pos + j] = data[j];
}
void me::bytebuff::push_uint32(uint32_t i)
{
  uint8_t* bytes = from_uint32(new uint8_t[4], i, byte_order);
  for (uint8_t j = 0; j < sizeof(uint32_t); j++)
    this->data[pos + j] = data[j];
}
void me::bytebuff::push_uint64(uint64_t i)
{
  uint8_t* bytes = from_uint64(new uint8_t[8], i, byte_order);
  for (uint8_t j = 0; j < sizeof(uint64_t); j++)
    this->data[pos + j] = data[j];
}

void me::bytebuff::flush()
{
  delete[] data;
}
