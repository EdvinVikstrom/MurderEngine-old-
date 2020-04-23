#include "image_format.h"
#include "audio_format.h"
#include "scene_format.h"
#include "../kernel/io/file_reader.h"

#include "formats/bmp/bmp_format.h"
#include "formats/png/png_format.h"
#include "formats/wave/wave_format.h"
#include "formats/collada/collada_format.h"

static std::vector<me::format::image_format*> image_formats;
static std::vector<me::format::audio_format*> audio_formats;
static std::vector<me::format::scene_format*> scene_formats;

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

void me::format::loadImage(MeInstance* instance, const std::string &filepath, me::Image* image)
{
  me::fileattr &file = *me::load_file(image->info.source.empty() ? filepath.c_str() : image->info.source.c_str());
  image_format* format = find_image_format(file);
  format->load_image(file, image);
}
void me::format::loadAudio(MeInstance* instance, const std::string &filepath, me::AudioTrack* track)
{
  me::fileattr &file = *me::load_file(filepath.c_str());
  audio_format* format = find_audio_format(file);
  format->load_audio(file, track);
}
void me::format::loadScene(MeInstance* instance, const std::string &filepath, me::ScenePacket* packet)
{
  me::fileattr &file = *me::load_file(filepath.c_str());
  scene_format* format = find_scene_format(file);
  format->load_scene(file, packet);

  for (auto const &[key, value] : packet->images) { loadImage(instance, "", value); instance->loadImage(value); }
  for (auto const &[key, value] : packet->meshes) { formatMesh(value, MeshFormat::MESH_FORMAT_VNTC); instance->loadMesh(value); }
  for (auto const &[key, value] : packet->lights) instance->loadLight(value);
}

void me::format::writeImage(MeInstance* instance, const std::string &filepath, me::format::ImageFileFormat image_format, me::Image* image)
{
  me::write_buffer buffer;
  for (me::format::image_format* format : image_formats)
  {
    if (format->format == image_format)
      format->write_image(buffer, image);
  }
  me::write_file(filepath.c_str(), &buffer.bytes[0], 0, buffer.length());
}

unsigned char* me::format::loadRAWData(MeInstance* instance, const std::string &filepath, uint32_t &length)
{
  me::fileattr &file = *me::load_file(filepath.c_str());
  file.readFile();
  length = file.buffer->length;
  return file.buffer->data;
}

void me::format::init()
{
  image_formats.push_back(new bmp_format);
  image_formats.push_back(new png_format);
  audio_formats.push_back(new wave_format);
  scene_formats.push_back(new collada_format);
}
void me::format::cleanup()
{
  // TODO:
}
