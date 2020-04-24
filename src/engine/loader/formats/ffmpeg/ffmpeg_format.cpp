#include "ffmpeg_format.h"

int load_image(me::fileattr &file, me::Image* image)
{
  
  return ME_FINE;
}

int write_image(me::bytebuff &buffer, me::Image* image)
{
  return ME_FINE;
}

bool recognized(me::fileattr &file)
{
  return me::str_ends(file.filepath, ".ffmpeg");
}

std::vector<std::string> get_file_exts()
{
  return { "ffmpeg" };
}
