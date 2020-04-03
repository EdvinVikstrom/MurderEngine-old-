#include "blender_reader.h"
#include "../../../utilities/StringUtils.h"
#include "../../../utilities/Logger.h"

int read_blender(me::file_state &file, me::scene_packet* scene)
{
  return ME_FINE;
}

bool recognized(me::file_state &file)
{
  return me_utils::strEndsWith(".blend") || me_utils::strEndsWith(".blend1") || (
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
