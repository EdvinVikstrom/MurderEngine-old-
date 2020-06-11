#ifndef PNG_CHUNKS_H
  #define PNG_CHUNKS_H

struct png_chunk_hdri {
  uint32_t width;
  uint32_t height;
  uint8_t bitDepth;
  uint8_t colorType;
  uint8_t compression;
  uint8_t filter;
  uint8_t interlace;

  png_chunk_hdri(png_chunk &chunk)
  {
    width = me::bytebuff::to_uint32(chunk.data, 0, me::ByteOrder::BO_LITTLE_ENDIAN);
    height = me::bytebuff::to_uint32(chunk.data, 4, me::ByteOrder::BO_LITTLE_ENDIAN);
    bitDepth = chunk.data[8];
    colorType = chunk.data[9];
    compression = chunk.data[10];
    filter = chunk.data[11];
    interlace = chunk.data[12];
  }

};

struct png_chunk_plte {
  uint32_t entries;
  uint8_t *red, *green, *blue;

  png_chunk_plte(png_chunk &chunk)
  {
    entries = chunk.length / 3;
    red = new uint8_t[entries];
    green = new uint8_t[entries];
    blue = new uint8_t[entries];
    for (uint32_t i = 0; i < chunk.length; i+=3)
    {
      red[i / 3] = chunk.data[i];
      green[i / 3] = chunk.data[i+1];
      blue[i / 3] = chunk.data[i+2];
    }
  }

};

struct png_chunk_trns {
  uint32_t entries;
  uint8_t* alphaData;

  png_chunk_trns(png_chunk &chunk)
  {
    entries = chunk.length;
    alphaData = new uint8_t[entries];
    for (uint32_t i = 0; i < chunk.length; i++)
      alphaData[i] = chunk.data[i];
  }

  inline uint32_t get_alpha(uint32_t index, uint16_t bit_depth)
  {
    if (bit_depth == 8)
      return alphaData[index];
    else if (bit_depth == 16)
     return me::bytebuff::to_uint16(alphaData, index * 2, me::ByteOrder::BO_LITTLE_ENDIAN);
    else if (bit_depth == 24)
      return me::bytebuff::to_uint24(alphaData, index * 3, me::ByteOrder::BO_LITTLE_ENDIAN);
    else if (bit_depth == 32)
      return me::bytebuff::to_uint32(alphaData, index * 4, me::ByteOrder::BO_LITTLE_ENDIAN);
    return 0;
  }

};

#endif