#include "jpeg_reader.h"

int me::format::jpeg_format::read_image(me::fileattr &file, me::image* image)
{
  return ME_FINE;
}
bool me::format::jpeg_format::recognized(me::fileattr &file)
{
  return me::str_ends(file.filepath, ".jpg") || me::str_ends(file.filepath, ".jpeg");
}
std::vector<std::string> me::format::jpeg_format::get_file_exts()
{
  return { "jpg", "jpeg", "jpe", "jfif", "jif" };
}
