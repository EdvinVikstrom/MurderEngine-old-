#include "lzw_algorithm.h"
#include "../../math/maths.h" // remove maybe not

#define LZW_EOI_CODE          257
#define LZW_CLEAR_CODE        256
#define LZW_FIRST_CODE        258

void me::lzw_algorithm::init_encoding_string_table()
{
  for (uint16_t i = 0; i < 256; i++)
  {
    std::string str = "";
    str+=(char) i;
    encodingTable[str] = i;
  }
}

void me::lzw_algorithm::init_decoding_string_table()
{
  for (uint16_t i = 0; i < 256; i++)
  {
    std::string str = "";
    str+=(char) i;
    decodingTable[i] = str;
  }
}

int me::lzw_algorithm::decode(me::bytebuff &input, me::bytebuff &output)
{
  uint16_t bits = 9;
  uint32_t max = (uint32_t) me::maths::pow(2.0D, (double) bits);
  uint32_t count = 256;
  init_decoding_string_table();
  uint16_t old = input.pull_bits(bits), n;
  std::string str = decodingTable[old];
  std::string code = "";
  code+=str[0];
  output.push((uint8_t) str[0]);
  while(input.hasRemaining())
  {
    n = input.pull_bits(bits);
    if (decodingTable.find(n) == decodingTable.end())
    {
      str = decodingTable[old];
      str = str + code;
    }else
      str = decodingTable[n];
    output.push((uint8_t*) &str[0], str.size());
    code = "";
    code+=str[0];
    decodingTable[count] = decodingTable[old] + code;
    count++;
    old = n;
    if (count >= max-1)
    {
      bits++;
      max = (uint32_t) me::maths::pow(2.0D, (double) bits);
    }
  }
  return ME_FINE;
}

int me::lzw_algorithm::encode(me::bytebuff &input, me::bytebuff &output)
{
  uint16_t bits = 9;
  uint32_t max = (uint32_t) me::maths::pow(2.0D, (double) bits);
  uint32_t count = 256;
  init_encoding_string_table();
  std::string prev = "";
  std::string code = "";
  prev+=(char) input.pull();
  while(input.hasRemaining())
  {
    code+=(char) input.pull();
    if (encodingTable.find(prev + code) != encodingTable.end())
      prev = prev + code;
    else
    {
      output.push_bits(encodingTable[prev], bits);
      encodingTable[prev + code] = count;
      count++;
      prev = code;
      if (count >= max)
      {
        bits++;
        max = (uint32_t) me::maths::pow(2.0D, (double) bits);
      }
    }
    code = "";
  }
  output.push_bits(encodingTable[prev], bits);
  return ME_FINE;
}
