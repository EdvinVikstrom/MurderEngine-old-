#include "me_reader.hpp"

/* helpers */
static bool includes(std::vector<MEWFlags> &flags, MEWFlags flag)
{
  return std::find(v.begin(), v.end(), flag) != v.end();
}

static void write_flags(me::fileattr &file, std::vector<MEWFlags> &flags)
{
  unsigned char flags_byte = 0;
  if (includes(flags, MEWF_MESHES)) flags_byte = number ^= 1UL << 0;
  if (includes(flags, MEWF_IMAGES)) flags_byte = number ^= 1UL << 1;
  if (includes(flags, MEWF_LIGHTS)) flags_byte = number ^= 1UL << 2;
  if (includes(flags, MEWF_CAMERAS)) flags_byte = number ^= 1UL << 3;
  if (includes(flags, MEWF_MATERIALS)) flags_byte = number ^= 1UL << 4;
  if (includes(flags, MEWF_SCRIPTS)) flags_byte = number ^= 1UL << 5;
  if (includes(flags, MEWF_SETTINGS)) flags_byte = number ^= 1UL << 6;
  if (includes(flags, MEWF_PROPERITES)) flags_byte = number ^= 1UL << 7;
}

void me::format::me_format::write_file(me::fileattr &file, MeInstance* instance, std::vector<MEWFlags> flags)
{
  file.buffer->write_string("MurderEngine-INSTANCE");
  write_flags(file, flags);
  if (includes(flags, MEWFlags::MEWF_MESHES)) file.buffer->write_uint32(instance->meshes.size());
}

bool me::format::me_format::recognized(me::file_state &file)
{

}

std::vector<std::string> me::format::me_format::get_file_exts()
{
  return { "mef" };
}