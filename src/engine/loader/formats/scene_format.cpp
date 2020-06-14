#include "scene_format.hpp"

static std::vector<me::format::SceneFormat*> formats;

void me::format::initSceneFormats()
{

}

void me::format::cleanupSceneFormats()
{
  for (me::format::SceneFormat* format : formats)
  delete format;
  formats.clear();
}

int me::reader::readScene(const std::string &filepath, me::Scene* scene, uint64_t flags)
{
  me::filebuff* file = me::loadFile(filepath)->readFile();
  me::format::SceneFileFormat format = me::format::SceneFileFormat::SFF_NAN;
  for (me::format::SceneFormat* sceneFormat : formats)
  {
    if (sceneFormat->recognized(file))
    {
      format = sceneFormat->format;
      break;
    }
  }
  return readScene(file->buffer, format, scene, flags);
}

int me::reader::readScene(me::bytebuff* buffer, me::format::SceneFileFormat format, me::Scene* scene, uint64_t flags)
{
  for (me::format::SceneFormat* sceneFormat : formats)
  {
    if (sceneFormat->format == format)
      return sceneFormat->readScene(*buffer, scene, flags);
  }
  return ME_FORMAT_NOT_FOUND;
}

int me::writer::writeScene(me::bytebuff* buffer, me::format::SceneFileFormat format, me::Scene* scene, uint64_t flags)
{
  for (me::format::SceneFormat* sceneFormat : formats)
  {
    if (sceneFormat->format == format)
      return sceneFormat->writeScene(*buffer, scene, flags);
  }
  return ME_FORMAT_NOT_FOUND;
}
