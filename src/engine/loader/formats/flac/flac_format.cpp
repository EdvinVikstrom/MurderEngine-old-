#include "flac_format.h"

int me::format::flac_format::load_audio(me::bytebuff &buffer, me::AudioTrack* track, uint64_t flags)
{
  return ME_FINE;
}

bool me::format::flac_format::recognized(me::fileattr &file)
{
  return me::str_ends(file.filepath, ".flac");
}

std::vector<std::string> me::format::flac_format::get_file_exts()
{
  return { "flac" };
}

uint64_t me::format::flac_format::supported_flags()
{
  return 0; // TODO:
}
