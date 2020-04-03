#include "png_reader.h"
#include "../../../kernel/common/byte_buffer.h"
#include "../../../utilities/StringUtils.h"
#include "../../../utilities/Logger.h"

static me::log* PNG = new me::log("PNG",
"\e[33m[%N] %T #%M \e[0m",
"\e[33m[%N] %T #%M \e[0m",
"\e[33m[%N] %T\e[0m \e[31m#%M \e[0m",
"\e[34m[%N] %T #%M \e[0m"
);

int me::fformat::png_reader::read_image(me::file_state &file, me::image* image)
{
  return ME_FINE;
}

bool me::fformat::png_reader::recognized(me::file_state &file)
{
  return me_utils::strEndsWith(file.filepath, ".png") || (
    file.data[0] == 137 &&
    file.data[1] == 80 &&
    file.data[2] == 78 &&
    file.data[3] == 71 &&
    file.data[4] == 13 &&
    file.data[5] == 10 &&
    file.data[6] == 26 &&
    file.data[7] == 10
  );
}

std::vector<std::string> me::fformat::png_reader::get_file_exts()
{
  return { "png" };
}
