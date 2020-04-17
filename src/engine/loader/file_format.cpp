#include "image_format.h"
#include "mesh_format.h"
#include "../kernel/io/file_reader.h"

#include "formats/bmp/bmp_format.h"
#include "formats/png/png_format.h"
#include "formats/collada/collada_format.h"

static std::vector<me::format::file_format*> formats;

static me::format::file_format* find_format(me::format::FileType type, me::fileattr &file)
{
  for (me::format::file_format* format : formats)
  {
    if (format->type == type && format->recognized(file))
      return format;
  }
  return nullptr;
}

void me::format::read_image(MeInstance* instance, const std::string &filepath, me::image* image)
{
  me::fileattr &file = *me::read_file(image->source.empty() ? filepath.c_str() : image->source.c_str());
  file_format* format = find_format(FTYPE_IMAGE, file);
  ((image_format*)format)->read_file(file, image);
}
void me::format::read_mesh(MeInstance* instance, const std::string &filepath, me::scene_packet* packet)
{
  me::fileattr &file = *me::read_file(filepath.c_str());
  file_format* format = find_format(FTYPE_MESH, file);
  ((mesh_format*)format)->read_file(file, packet);

  /* read and load images to memory */
  for (auto const &[key, value] : packet->images) { read_image(instance, "", value); instance->loadImage(value); }

  /* load meshes to memory */
  for (auto const &[key, value] : packet->meshes) { formatMesh(value, MeshFormat::MESH_FORMAT_VNTC); instance->loadMesh(value); }

  /* load lights to memory */
  for (auto const &[key, value] : packet->lights) instance->loadLight(value);
}

void me::format::init()
{
  formats.push_back(new bmp_format);
  formats.push_back(new png_format);
  formats.push_back(new collada_format);
}
void me::format::cleanup()
{

}
