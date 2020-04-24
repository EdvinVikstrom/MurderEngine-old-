/* *THIS CLASS CAN BE VERY CONFUSING */

#include "file_reader.h"
#include "../../math/maths.h"

#include <iostream> // remove

#define BIT_POS_0         1
#define BIT_POS_1         2
#define BIT_POS_2         4
#define BIT_POS_3         8
#define BIT_POS_4         16
#define BIT_POS_5         32
#define BIT_POS_6         64
#define BIT_POS_7         128

static unsigned char* BIT_POS = new unsigned char[8] {
  BIT_POS_0,
  BIT_POS_1,
  BIT_POS_2,
  BIT_POS_3,
  BIT_POS_4,
  BIT_POS_5,
  BIT_POS_6,
  BIT_POS_7
};

void me::bytebuff::byteOrder(me::ByteOrder order)
{
  byte_order = order;
}
void me::bytebuff::bitOrder(me::BitOrder order)
{
  bit_order = order;
}

void me::bytebuff::pushMem(uint64_t mem)
{
  data.reserve(data.size() + mem);
}
void me::bytebuff::flip()
{
  pos != 0 ? 0 : length - 1;
  bit_pos != 0 ? 0 : (length * 8L) - 1;
}
bool me::bytebuff::hasRemaining()
{
  return pos < length;
}
uint64_t me::bytebuff::remaining()
{
  return length - pos;
}
uint8_t me::bytebuff::read()
{
  bit_pos+=8;
  return data[pos++];
}
void me::bytebuff::write(unsigned char byte)
{
  bit_pos+=8;
  pos++;
  data.emplace_back(byte);
}

uint8_t* me::bytebuff::read(uint64_t bit_length, uint64_t byte_length)
{
  unsigned char* bytes = new unsigned char[byte_length];
  uint32_t byte_pos = 0;
  for (uint64_t i = 0; i < bit_length; i++)
  {
    if (bit_order == me::BitOrder::BO_FIRST)
      bytes[byte_pos]+=data[pos] & BIT_POS[i % 8L];
    else
      bytes[byte_pos]+=data[pos] & BIT_POS[(7 - i) % 8L];
    bit_pos++;
    if (i % 8L == 7L)
    {
      byte_pos++;
      pos++;
    }
  }
  return bytes;
}
void me::bytebuff::write(uint8_t* bytes, uint64_t bit_length, uint64_t byte_length)
{
}

unsigned char me::bytebuff::pull()
{
  bit_pos+=8;
  return data[pos++];
}
unsigned char* me::bytebuff::pull(uint32_t length)
{
  unsigned char* data = new unsigned char[length];
  for (uint32_t i = 0; i < length; i++)
    data[i] = this->data[pos++];
  bit_pos+=length * 8;
  return data;
}
short me::bytebuff::pull_int16()
{
  short i = 0;
  if (byte_order == me::ByteOrder::BO_LITTLE_ENDIAN) i = (data[pos++] << 8) | (data[pos++]);
  else i = (data[pos++]) | (data[pos++] << 8);
  bit_pos+=16;
  return i;
}
int me::bytebuff::pull_int24()
{
  int i = 0;
  if (byte_order == me::ByteOrder::BO_LITTLE_ENDIAN) i = (data[pos++] << 16) | (data[pos++] << 8) | (data[pos++]);
  else i = (data[pos++]) | (data[pos++] << 8) | (data[pos++] << 16);
  bit_pos+=24;
  return i;
}
int me::bytebuff::pull_int32()
{
  int i = 0;
  if (byte_order == me::ByteOrder::BO_LITTLE_ENDIAN) i = (data[pos++] << 24) | (data[pos++] << 16) | (data[pos++] << 8) | (data[pos++]);
  else i = (data[pos++]) | (data[pos++] << 8) | (data[pos++] << 16) | (data[pos++] << 24);
  bit_pos+=32;
  return i;
}
long me::bytebuff::pull_int64()
{
  long i = 0;
  if (byte_order == me::ByteOrder::BO_LITTLE_ENDIAN) i = (data[pos++] << 56) | (data[pos++] << 48) | (data[pos++] << 40) | (data[pos++] << 32) | (data[pos++] << 24) | (data[pos++] << 16) | (data[pos++] << 8) | (data[pos++]);
  else i = (data[pos++]) | (data[pos++] << 8) | (data[pos++] << 16) | (data[pos++] << 24) | (data[pos++] << 32) | (data[pos++] << 40) | (data[pos++] << 48) | (data[pos++] << 56);
  bit_pos+=64;
  return i;
}

uint16_t me::bytebuff::pull_uint16()
{
  uint16_t i = 0;
  if (byte_order == me::ByteOrder::BO_LITTLE_ENDIAN) i = (data[pos++] << 8) | (data[pos++]);
  else i = (data[pos++]) | (data[pos++] << 8);
  bit_pos+=16;
  return i;
}
uint32_t me::bytebuff::pull_uint24()
{
  uint32_t i = 0;
  if (byte_order == me::ByteOrder::BO_LITTLE_ENDIAN) i = (data[pos++] << 16) | (data[pos++] << 8) | (data[pos++]);
  else i = (data[pos++]) | (data[pos++] << 8) | (data[pos++] << 16);
  bit_pos+=24;
  return i;
}
uint32_t me::bytebuff::pull_uint32()
{
  uint32_t i = 0;
  if (byte_order == me::ByteOrder::BO_LITTLE_ENDIAN) i = (data[pos++] << 24) | (data[pos++] << 16) | (data[pos++] << 8) | (data[pos++]);
  else i = (data[pos++]) | (data[pos++] << 8) | (data[pos++] << 16) | (data[pos++] << 24);
  bit_pos+=32;
  return i;
}
uint64_t me::bytebuff::pull_uint64()
{
  uint64_t i = 0;
  if (byte_order == me::ByteOrder::BO_LITTLE_ENDIAN) i = (data[pos++] << 56) | (data[pos++] << 48) | (data[pos++] << 40) | (data[pos++] << 32) | (data[pos++] << 24) | (data[pos++] << 16) | (data[pos++] << 8) | (data[pos++]);
  else i = (data[pos++]) | (data[pos++] << 8) | (data[pos++] << 16) | (data[pos++] << 24) | (data[pos++] << 32) | (data[pos++] << 40) | (data[pos++] << 48) | (data[pos++] << 56);
  bit_pos+=64;
  return i;
}

long me::bytebuff::pull_int(uint32_t bit_length)
{
}
uint64_t me::bytebuff::pull_uint(uint32_t bit_length)
{
}

void me::bytebuff::push(unsigned char byte)
{
  data.emplace_back(byte);
  pos++;
  bit_pos+=8;
}
void me::bytebuff::push(unsigned char* data, uint32_t length)
{
  pushMem(length);
  for (uint32_t i = 0; i < length; i++)
    this->data.emplace_back(data[i]);
  pos+=length;
  bit_pos+=length * 8;
}
void me::bytebuff::push_int16(short i)
{
  for (unsigned char j = 0; j < 8; j++)
    data.emplace_back(i >> (me::maths::abs((byte_order == me::ByteOrder::BO_LITTLE_ENDIAN ? 0 : 1) - j) * 8));
  pos+=2;
  bit_pos+=16;
}
void me::bytebuff::push_int24(int i)
{
  for (unsigned char j = 0; j < 8; j++)
    data.emplace_back(i >> (me::maths::abs((byte_order == me::ByteOrder::BO_LITTLE_ENDIAN ? 0 : 2) - j) * 8));
  pos+=3;
  bit_pos+=24;
}
void me::bytebuff::push_int32(int i)
{
  for (unsigned char j = 0; j < 8; j++)
    data.emplace_back(i >> (me::maths::abs((byte_order == me::ByteOrder::BO_LITTLE_ENDIAN ? 0 : 3) - j) * 8));
  pos+=4;
  bit_pos+=32;
}
void me::bytebuff::push_int64(long i)
{
  for (unsigned char j = 0; j < 8; j++)
    data.emplace_back(i >> (me::maths::abs((byte_order == me::ByteOrder::BO_LITTLE_ENDIAN ? 0 : 7) - j) * 8));
  pos+=8;
  bit_pos+=64;
}

void me::bytebuff::push_uint16(uint16_t i)
{
  for (unsigned char j = 0; j < 8; j++)
    data.emplace_back(i >> (me::maths::abs((byte_order == me::ByteOrder::BO_LITTLE_ENDIAN ? 0 : 1) - j) * 8));
  pos+=2;
  bit_pos+=16;
}
void me::bytebuff::push_uint24(uint32_t i)
{
  for (unsigned char j = 0; j < 8; j++)
    data.emplace_back(i >> (me::maths::abs((byte_order == me::ByteOrder::BO_LITTLE_ENDIAN ? 0 : 2) - j) * 8));
  pos+=3;
  bit_pos+=24;
}
void me::bytebuff::push_uint32(uint32_t i)
{
  for (unsigned char j = 0; j < 8; j++)
    data.emplace_back(i >> (me::maths::abs((byte_order == me::ByteOrder::BO_LITTLE_ENDIAN ? 0 : 3) - j) * 8));
  pos+=4;
  bit_pos+=32;
}
void me::bytebuff::push_uint64(uint64_t i)
{
  for (unsigned char j = 0; j < 8; j++)
    data.emplace_back(i >> (me::maths::abs((byte_order == me::ByteOrder::BO_LITTLE_ENDIAN ? 0 : 7) - j) * 8));
  pos+=8;
  bit_pos+=64;
}

void me::bytebuff::push_int(long i, uint32_t bit_length)
{
}
void me::bytebuff::push_uint(uint64_t i, uint32_t bit_length)
{
}

void me::bytebuff::flush()
{
  data.clear();
}
