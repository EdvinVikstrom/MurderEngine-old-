#include "image_reader.h"
#include "mesh_reader.h"
#include "../kernel/io/file_reader.h"

#include "modules/bmp/bmp_reader.h"
#include "modules/png/png_reader.h"
#include "modules/jpeg/jpeg_reader.h"
#include "modules/collada/collada_reader.h"

static std::vector<me::fformat::file_format*> formats;

void me::fformat::read_image(MeInstance* instance, const std::string &filepath, me::image* image)
{
  me::fileattr &file = *me::read_file(image->source.empty() ? filepath.c_str() : image->source.c_str());
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
}
void me::fformat::read_mesh(MeInstance* instance, const std::string &filepath, me::scene_packet* packet)
{
  me::fileattr &file = *me::read_file(filepath.c_str());
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
  /* read and load images to memory */
  for (auto const &[key, value] : packet->images) { read_image(instance, "", value); instance->loadImage(value); }

  /* load meshes to memory */
  for (auto const &[key, value] : packet->meshes) instance->loadMesh(value);

  /* load lights to memory */
  for (auto const &[key, value] : packet->lights) instance->loadLight(value);
}

void me::fformat::init()
{
  formats.push_back(new bmp_reader);
  formats.push_back(new png_reader);
  formats.push_back(new jpeg_reader);
  formats.push_back(new collada_reader);
}
void me::fformat::cleanup()
{

}
