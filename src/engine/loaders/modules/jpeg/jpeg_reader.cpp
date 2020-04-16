#include "jpeg_reader.h"

int me::fformat::jpeg_reader::read_image(me::fileattr &file, me::image* image)
{
  return ME_FINE;
}
bool me::fformat::jpeg_reader::recognized(me::fileattr &file)
{
  return me::str_ends(file.filepath, ".jpg") || me::str_ends(file.filepath, ".jpeg");
}
std::vector<std::string> me::fformat::jpeg_reader::get_file_exts()
{
  return { "jpg", "jpeg", "jpe", "jfif", "jif" };
}
