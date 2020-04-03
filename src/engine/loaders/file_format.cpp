#include "image_reader.h"
#include "mesh_reader.h"
#include "../kernel/io/file_reader.h"

#include "modules/bmp/bmp_reader.h"
#include "modules/png/png_reader.h"
#include "modules/collada/collada_reader.h"
#include "modules/wavefront/obj_reader.h"

static std::vector<me::fformat::file_format*> formats;

me::image* me::fformat::read_image(const std::string &filepath)
{
  me::file_state file = me::read_file(filepath);
  me::image* image = new me::image;
  for (me::fformat::file_format* format : formats)
  {
    if (format->getFormatType() != me::fformat::format_type::IMAGE)
      continue;
    if (format->recognized(file))
    {
      ((image_reader*)format)->read_file(file, image);
      break;
    }
  }
  return image;
}
me::scene_packet* me::fformat::read_mesh(const std::string &filepath)
{
  me::file_state file = me::read_file(filepath);
  me::scene_packet* packet = new me::scene_packet;
  for (me::fformat::file_format* format : formats)
  {
    if (format->getFormatType() != me::fformat::format_type::MESH)
      continue;
    if (format->recognized(file))
    {
      ((mesh_reader*)format)->read_file(file, packet);
      break;
    }
  }
  return packet;
}

void me::fformat::init()
{
  formats.push_back(new bmp_reader);
  formats.push_back(new collada_reader);
  formats.push_back(new obj_reader);
}
void me::fformat::cleanup()
{

}
