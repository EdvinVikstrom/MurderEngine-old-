#include "file_reader.h"

void me::bitbuff::push(uint8_t i)
{
  data.emplace_back(i);
  pos+=8;
}
void me::bitbuff::push_uint(uint64_t i, uint32_t length)
{
  uint32_t byte_pos = pos / 8;
  uint32_t size = length / 8;
  i = i >> (pos % 8L);
  for (uint32_t j = 0; j < size; j++)
  {
    if (byte_pos + j >= data.size())
      data.emplace_back(0);
    data[byte_pos + j] |= i;
  }
  pos+=length;
}

// AND
// 01001101
// 10110111
// 00000101

// OR
// 01001101
// 10100101
// 11101101

/*

  // simple
  01110101 10000000

  00000000 00000000

  // trickyyyy
  off: 3
  01110101 10000000

  10100000 00000000

*/
