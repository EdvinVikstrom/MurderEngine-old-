#include "bmp_reader.h"
#include "../../../utilities/StringUtils.h"

int me::fformat::bmp_reader::read_image(const std::string &file_name, unsigned char* data, uint32_t data_size, me::image* image)
{
  bmp_header header = {
    {
      (data[0] << 8 | data[1]);
      (data[2] << 24 | data[3] << 16 | data[4] << 8 | data[5]);
      (data[6] << 24 | data[7] << 16 | data[8] << 8 | data[9]);
      (data[10] << 24 | data[11] << 16 | data[12] << 8 | data[13]);
    };
    {
      (data[14] << 24 | data[15] << 16 | data[16] << 8 | data[17]);
      (data[18] << 24 | data[19] << 16 | data[20] << 8 | data[21]);
      (data[22] << 24 | data[23] << 16 | data[24] << 8 | data[25]);
      (data[26] << 8 | data[27]);
      (data[28] << 8 | data[29]);
      (data[30] << 24 | data[31] << 16 | data[32] << 8 | data[33]);
      (data[34] << 24 | data[35] << 16 | data[36] << 8 | data[37]);
      (data[38] << 24 | data[39] << 16 | data[40] << 8 | data[41]);
      (data[42] << 24 | data[43] << 16 | data[44] << 8 | data[45]);
      (data[46] << 24 | data[47] << 16 | data[48] << 8 | data[49]);
      (data[50] << 24 | data[51] << 16 | data[52] << 8 | data[53]);
    };
  };

  image->identifier = (std::string) file_name;
  image->width = header.info.width;
  image->height = header.info.height;
  uint32_t image_size = image->width * image->height * 4;

  if (header.info.bits_per_pixel==bmp_color_type.MONOCHROME)
    image->format = ME_TEX_FORMAT_BINARY;
  else if (header.info.bits_per_pixel==bmp_color_type.BIT4)
    image->format = ME_TEX_FORMAT_GRAY4;
  else if (header.info.bits_per_pixel==bmp_color_type.BIT8)
    image->format = ME_TEX_FORMAT_GRAY8;
  else if (header.info.bits_per_pixel==bmp_color_type.RGB16)
    image->format = ME_TEX_FORMAT_RGB16;
  else if (header.info.bits_per_pixel==bmp_color_type.RGB24)
    image->format = ME_TEX_FORMAT_RGB24;
  image->pixels = new unsigned char[image_size];
  for (unsigned int i = 0; i < image_size; i++)
    image->pixels[i] = data[header.head.data_offset+i];
  return ME_FINE;
}

bool me::fformat::bmp_reader::recognized(const std::string &file_name, unsigned char* data, uint32_t data_size)
{
  return me_utils::strEndsWith(file_name, ".bmp") || (data[0]=='b' && data[1]=='m');
}

std::vector<std::string> me::format::bmp_reader::get_file_exts()
{
  return { "bmp" };
}
