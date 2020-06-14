#include "ffmpeg_format.hpp"
//#include "../../../../external/ffmpeg/libavcodec/avcodec.h"
//#include "../../../../external/ffmpeg/libavformat/avformat.h"

int me::format::ffmpeg_format::load_image(me::bytebuff &buffer, me::Image* image, uint64_t flags)
{
  //AVFormatContext* format_context = avformat_alloc_context();
  //avformat_open_input(&format_context, buffer.source.c_str(), nullptr, nullptr);
  //std::cout << "format: " << format_context->iformat->name << "\n";
  //std::cout << "duration: " << format_context->duration << "\n";
  //std::cout << "bit rate: " << format_context->bit_rate << "\n";
  return ME_FINE;
}

int me::format::ffmpeg_format::write_image(me::bytebuff &buffer, me::Image* image, uint64_t flags)
{
  return ME_FINE;
}

bool me::format::ffmpeg_format::recognized(me::fileattr &file)
{
  return me::str_ends(file.filepath, ".mov");
}

std::vector<std::string> me::format::ffmpeg_format::get_file_exts()
{
  return { ".mp4" };
}

uint64_t me::format::ffmpeg_format::supported_flags()
{
  return 0; // TODO:
}
