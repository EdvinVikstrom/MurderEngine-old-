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

int me::fformat::png_reader::read_image(me::fileattr &file, me::image* image)
{
  return ME_FINE;
}

bool me::fformat::png_reader::recognized(me::fileattr &file)
{
  return strEndsWith(file.filepath, ".png") || (
    file.buffer->data[0] == 137 &&
    file.buffer->data[1] == 80 &&
    file.buffer->data[2] == 78 &&
    file.buffer->data[3] == 71 &&
    file.buffer->data[4] == 13 &&
    file.buffer->data[5] == 10 &&
    file.buffer->data[6] == 26 &&
    file.buffer->data[7] == 10
  );
}

std::vector<std::string> me::fformat::png_reader::get_file_exts()
{
  return { "png" };
}
