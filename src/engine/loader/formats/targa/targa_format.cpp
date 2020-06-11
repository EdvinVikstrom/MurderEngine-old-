#include "targa_format.hpp"

int me::format::targa_format::read_extension_area(me::bytebuff &buffer, targa_ext_area &ext_area)
{
  if (!buffer.canPull(sizeof(targa_ext_area)))
    return ME_ERR;

  ext_area.authorName = new uint8_t[41];
  ext_area.authorComment = new uint8_t[324];
  ext_area.dateTime = new uint8_t[12];
  ext_area.jobId = new uint8_t[41];
  ext_area.jobTime = new uint8_t[6];
  ext_area.softwareId = new uint8_t[41];
  ext_area.softwareVersion = new uint8_t[3];

  ext_area.size = buffer.pull_uint16();
  buffer.pull(ext_area.authorName, 41);
  buffer.pull(ext_area.authorComment, 324);
  buffer.pull(ext_area.dateTime, 12);
  buffer.pull(ext_area.jobId, 41);
  buffer.pull(ext_area.jobTime, 6);
  buffer.pull(ext_area.softwareId, 41);
  buffer.pull(ext_area.softwareVersion, 3);
  ext_area.keyColor = buffer.pull_uint32();
  ext_area.aspectRatio = buffer.pull_uint32();
  ext_area.gamma = buffer.pull_uint32();
  ext_area.colorCorrectionOffset = buffer.pull_uint32();
  ext_area.postageStampOffset = buffer.pull_uint32();
  ext_area.scanLineOffset = buffer.pull_uint32();
  ext_area.attribType = buffer.pull();
  return ME_FINE;
}

int me::format::targa_format::read_header(me::bytebuff &buffer, targa_header &header)
{
  if (!buffer.canPull(sizeof(header)))
    return ME_ERR;
  header.idLength = buffer.pull();
  header.colorMapType = buffer.pull();
  header.imageType = buffer.pull();

  header.colorMapSpec.entryIndex = buffer.pull_uint16();
  header.colorMapSpec.mapLength = buffer.pull_uint16();
  header.colorMapSpec.mapEntrySize = buffer.pull();

  header.imageSpec.xOrigin = buffer.pull_uint16();
  header.imageSpec.yOrigin = buffer.pull_uint16();
  header.imageSpec.width = buffer.pull_uint16();
  header.imageSpec.height = buffer.pull_uint16();
  header.imageSpec.pixelDepth = buffer.pull();
  header.imageSpec.imageDescriptor = buffer.pull();
  return ME_FINE;
}

int me::format::targa_format::decode(me::bytebuff &buffer, me::Image* image, targa_header &header)
{
  
  return ME_FINE;
}

int me::format::targa_format::load_image(me::bytebuff &buffer, me::Image* image, uint64_t flags)
{
  targa_version version = TARGA_V2_0;
  targa_header header;
  targa_ext_area ext_area;
  if (read_header(buffer, header) != ME_FINE)
  {
    std::cout << "[TARGALoader] [ERR]: failed to read targa header\n";
    return ME_ERR;
  }
  if (version >= TARGA_V2_0)
  {
    if (read_extension_area(buffer, ext_area))
    {
      std::cout << "[TARGALoader] [ERR]: failed to read extension area\n";
      return ME_ERR;
    }
    for (uint32_t i = 0; i < 41; i++)
      std::cout << ext_area.authorName[i];
    std::cout << "\n";
  }
  return ME_FINE;
}

int me::format::targa_format::write_image(me::bytebuff &buffer, me::Image* image, uint64_t flags)
{
  return ME_FINE;
}

bool me::format::targa_format::recognized(me::fileattr &file)
{
  return me::str_ends(file.filepath, ".tga") || me::str_ends(file.filepath, ".targa");
}

std::vector<std::string> me::format::targa_format::get_file_exts()
{
  return { "tga", "targa" };
}

uint64_t me::format::targa_format::supported_flags()
{
  return 0; // TODO:
}