#include "file_format.h"
#include "image_reader.h"
#include "mesh_reader.h"
#include "../kernel/io/file_reader.h"

// image
#include "modules/bmp/bmp_reader.h"

// mesh
#include "modules/collada/collada_reader.h"

void me::fformat::init()
{
  // image
  formats.push_back(new bmp_reader);
  // mesh
  formats.push_back(new collada_reader);
}

me::image* me::fformat::read_image(const std::string &filepath)
{
  uint64_t data_size;
  unsigned char* data = me::read_file(filepath, data_size);
  me::image* image;
  for (me::fformat::file_format* format : formats)
  {
    if (format->getFormatType() != me::fformat::format_type.IMAGE)
      continue;
    if (format->recognized(filepath, data, data_size))
    {
      ((image_reader*)format)->read_file(filepath, data, data_size, image);
      break;
    }
  }
  return image;
}
std::vector<me::item*> me::fformat::read_mesh(const std::string &filepath)
{
  uint64_t data_size;
  unsigned char* data = me::read_file(filepath, data_size);
  std::vector<me::item*> items;
  for (me::fformat::file_format* format : formats)
  {
    if (format->getFormatType() != me::fformat::format_type.IMAGE)
      continue;
    if (format->recognized(filepath, data, data_size))
    {
      ((mesh_reader*)format)->read_file(filepath, data, data_size, items);
      break;
    }
  }
  return items;
}
