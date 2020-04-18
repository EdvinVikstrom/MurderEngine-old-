#include "image_format.h"
#include "scene_format.h"
#include "../kernel/io/file_reader.h"

#include "formats/bmp/bmp_format.h"
#include "formats/png/png_format.h"
#include "formats/collada/collada_format.h"

static std::vector<me::format::file_format*> formats;

static me::format::file_format* find_format(me::format::FileType type, me::fileattr &file)
{
  for (me::format::file_format* format : formats)
  {
    /* checking if the type is the same as param[0] and if the format recognizes the file */
    if (format->type == type && format->recognized(file))
      return format;
  }
  /* if not found return "nullptr" */
  return nullptr;
}

void me::format::loadImage(MeInstance* instance, const std::string &filepath, me::Image* image)
{
  me::fileattr &file = *me::read_file(image->info.source.empty() ? filepath.c_str() : image->info.source.c_str());

  /* finding a "file reader" that recognizes the file format */
  file_format* format = find_format(FTYPE_IMAGE, file);
  /* casting to "image_format" and reading image data */
  ((image_format*)format)->read_file(file, image);
}
void me::format::loadScene(MeInstance* instance, const std::string &filepath, me::ScenePacket* packet)
{
  me::fileattr &file = *me::read_file(filepath.c_str());

  /* same as the "read_image()" */
  file_format* format = find_format(FTYPE_SCENE, file); // TODO: errors
  /* casting to "mesh_format" so we can use it as a "mesh reader". */
  ((scene_format*)format)->read_file(file, packet);

  /* read and load images to memory */
  for (auto const &[key, value] : packet->images) { loadImage(instance, "", value); instance->loadImage(value); }

  /* load meshes to memory */
  for (auto const &[key, value] : packet->meshes) { formatMesh(value, MeshFormat::MESH_FORMAT_VNTC); instance->loadMesh(value); }

  /* load lights to memory */
  for (auto const &[key, value] : packet->lights) instance->loadLight(value);
}

void me::format::init()
{
  /* adding "file readers" to the list */
  formats.push_back(new bmp_format);
  formats.push_back(new png_format);
  formats.push_back(new collada_format);
}
void me::format::cleanup()
{
  // TODO:
}
