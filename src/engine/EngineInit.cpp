#include "EngineInit.hpp"

#include "loader/formats/image_format.hpp"
#include "loader/formats/scene_format.hpp"
#include "audio/audio_system.hpp"

void meInitEverything()
{
  me::format::initImageFormats();
  me::format::initSceneFormats();
  me::audio::init();
}

void meCleanupEverything()
{
  me::format::cleanupImageFormats();
  me::format::cleanupSceneFormats();
  me::audio::cleanup();
}
