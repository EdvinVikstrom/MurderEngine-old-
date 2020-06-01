#include "image_format.h"
#include "audio_format.h"
#include "scene_format.h"
#include "archive_format.h"
#include "../kernel/io/file_reader.h"

/* image formats */
#include "formats/bmp/bmp_format.h"
#include "formats/png/png_format.h"
#include "formats/ico/ico_format.h"
#include "formats/jpeg/jpeg_format.h"
#include "formats/tiff/tiff_format.h"
#include "formats/targa/targa_format.h"

#include "formats/ffmpeg/ffmpeg_format.h"

/* audio formats */
#include "formats/wave/wave_format.h"
#include "formats/flac/flac_format.h"

/* scene formats */
#include "formats/collada/collada_format.h"

/* archive formats */
#include "formats/zip/zip_format.h"

static std::vector<me::format::image_format*> image_formats;
static std::vector<me::format::audio_format*> audio_formats;
static std::vector<me::format::scene_format*> scene_formats;
static std::vector<me::format::archive_format*> archive_formats;

static me::format::image_format* find_image_format(me::fileattr &file)
{
  for (me::format::image_format* format : image_formats)
  {
    if (format->recognized(file))
      return format;
  }
  return nullptr;
}

static me::format::audio_format* find_audio_format(me::fileattr &file)
{
  for (me::format::audio_format* format : audio_formats)
  {
    if (format->recognized(file))
      return format;
  }
  return nullptr;
}

static me::format::scene_format* find_scene_format(me::fileattr &file)
{
  for (me::format::scene_format* format : scene_formats)
  {
    if (format->recognized(file))
      return format;
  }
  return nullptr;
}

static me::format::archive_format* find_archive_format(me::fileattr &file)
{
  for (me::format::archive_format* format : archive_formats)
  {
    if (format->recognized(file))
      return format;
  }
  return nullptr;
}

void me::format::loadImage(MeInstance* instance, const std::string &filepath, me::Image* image, uint64_t flags)
{
  me::fileattr &file = *me::load_file(image->info.source.empty() ? filepath.c_str() : image->info.source.c_str());
  image_format* format = find_image_format(file);
  if (format != nullptr)
  {
    file.readFile();
    format->load_image(*file.buffer, image, flags);
    instance->storage.registerItem(1, image);
  }
}
void me::format::loadAudio(MeInstance* instance, const std::string &filepath, me::AudioTrack* track, uint64_t flags)
{
  me::fileattr &file = *me::load_file(filepath.c_str());
  audio_format* format = find_audio_format(file);
  if (format != nullptr)
  {
    file.readFile();
    format->load_audio(*file.buffer, track, flags);
  }
}
void me::format::loadScene(MeInstance* instance, const std::string &filepath, me::ScenePacket* packet, uint64_t flags)
{
  me::fileattr &file = *me::load_file(filepath.c_str());
  scene_format* format = find_scene_format(file);
  if (format != nullptr)
  {
    file.readFile();
    format->load_scene(*file.buffer, packet, flags);

    for (auto const &[key, value] : packet->images) { loadImage(instance, "", value, flags); }
    for (auto const &[key, value] : packet->meshes) { formatMesh(value, MeshFormat::MESH_FORMAT_VNTC); instance->storage.registerItem(0, value); }
  }
}
void me::format::loadArchive(MeInstance* instance, const std::string &filepath, me::Archive* archive, uint64_t flags)
{
  me::fileattr &file = *me::load_file(filepath.c_str());
  archive_format* format = find_archive_format(file);
  if (format != nullptr)
  {
    file.readFile();
    format->load_archive(*file.buffer, archive, flags);
  }
}

void me::format::writeImage(MeInstance* instance, const std::string &filepath, me::format::ImageFileFormat image_format, me::Image* image, uint64_t flags)
{
  me::bytebuff buffer(filepath, 0, me::ByteOrder::BO_BIG_ENDIAN, me::BitOrder::BO_LAST, me::ByteBuffMode::BBMODE_READ);
  for (me::format::image_format* format : image_formats)
  {
    if (format->format == image_format)
      format->write_image(buffer, image, flags);
  }
  me::write_file(filepath.c_str(), &buffer.data[0], 0, buffer.length);
}

unsigned char* me::format::loadRAWData(MeInstance* instance, const std::string &filepath, uint32_t &length)
{
  me::fileattr &file = *me::load_file(filepath.c_str());
  file.readFile();
  length = file.buffer->length;
  return &file.buffer->data[0];
}

void me::format::init()
{
  image_formats.push_back(new ffmpeg_format);
  image_formats.push_back(new png_format);
  image_formats.push_back(new targa_format);
  image_formats.push_back(new ico_format);
  image_formats.push_back(new jpeg_format);
  image_formats.push_back(new tiff_format);
  image_formats.push_back(new bmp_format);
  audio_formats.push_back(new wave_format);
  audio_formats.push_back(new flac_format);
  scene_formats.push_back(new collada_format);
  archive_formats.push_back(new zip_format);
}
void me::format::cleanup()
{
  // TODO:
}
