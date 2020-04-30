#include "jpeg_format.h"

int me::format::jpeg_format::read_header(me::bytebuff &buffer, jpeg_header &header)
{
  while(buffer.hasRemaining())
  {
    uint8_t byte = buffer.pull();
    if (byte == 0xFF)
    {
      uint8_t marker = buffer.pull();
      std::cout << marker << " m\n";
      if (marker == JPEG_MARKER_SOI) header.SOI = marker;
      else if (marker == JPEG_MARKER_DHT) header.DHT.read(buffer);
      else if (marker == JPEG_MARKER_DQT) header.DQT.read(buffer);
      else if (marker == JPEG_MARKER_DRI) header.DRI.read(buffer);
      else if (marker == JPEG_MARKER_SOS) header.SOS.read(buffer);
      else if (marker == JPEG_MARKER_COM) header.COM.read(buffer);
      else if (marker & 0xF0 == JPEG_MARKER_RST)
      {
        uint8_t n = marker & 0x0F;
        header.RST[n] = marker;
      }else if (marker & 0xF0 == JPEG_MARKER_SOF)
      {
        uint8_t n = marker & 0x0F;
        header.SOF[n].read(buffer);
      }else if (marker & 0xF0 == JPEG_MARKER_APP)
      {
        uint8_t n = marker & 0x0F;
        header.APP[n].read(buffer);
      }else if (marker == JPEG_MARKER_EOI) header.EOI = marker;
    }
  }
  return ME_FINE;
}

int me::format::jpeg_format::load_image(me::bytebuff &buffer, me::Image* image, uint64_t flags)
{
  jpeg_header header;
  if (read_header(buffer, header) != ME_FINE)
  {
    std::cout << "[JPEGLoader] [ERR]: failed to read JPEG header\n";
    return ME_ERR;
  }
  for (uint16_t i = 0; i < header.APP[0].length; i++)
    std::cout << header.APP[0].info[i];
  std::cout << "\n";
  return ME_FINE;
}

int me::format::jpeg_format::write_image(me::bytebuff &buffer, me::Image* image, uint64_t flags)
{
  return ME_FINE;
}

bool me::format::jpeg_format::recognized(me::fileattr &file)
{
  return me::str_ends(file.filepath, ".jpg") || me::str_ends(file.filepath, ".jpeg");
}

std::vector<std::string> me::format::jpeg_format::get_file_exts()
{
  return { "jpg", "jpeg", "jpe", "jfif", "jif" };
}

uint64_t me::format::jpeg_format::supported_flags()
{
  return 0; // TODO:
}
