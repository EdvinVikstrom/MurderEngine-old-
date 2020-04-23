#include "EngineInit.h"

#include "loader/file_format.h"
#include "audio/audio_system.h"

void meInitEverything()
{
  me::format::init();
  me::audio::init();
}

void meCleanupEverything()
{
  me::audio::cleanup();
}
