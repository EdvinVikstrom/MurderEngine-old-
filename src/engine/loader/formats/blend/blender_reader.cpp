#include "blender_reader.hpp"
#include "../../../utilities/StringUtils.hpp"
#include "../../../utilities/Logger.hpp"

int read_blender(me::file_state &file, me::scene_packet* scene)
{
  return ME_FINE;
}

bool recognized(me::file_state &file)
{
  return strEndsWith(file.filepath, ".blend") || strEndsWith(file.filepath, ".blend1") || (
  file.data[0] == 'B' &&
  file.data[1] == 'L' &&
  file.data[2] == 'E' &&
  file.data[3] == 'N' &&
  file.data[4] == 'D' &&
  file.data[5] == 'E' &&
  file.data[6] == 'R'
  );
}

std::vector<std::string> get_file_exts()
{
  return { "blend", "blend1" };
}
