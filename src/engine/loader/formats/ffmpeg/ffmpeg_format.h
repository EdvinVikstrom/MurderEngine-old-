#ifndef FFMPEG_FORMAT_H
  #define FFMPEG_FORMAT_H

#include "../../image_format.h"

namespace me {

  namespace format {

    struct ffmpeg_format : image_format {

      ffmpeg_format() : image_format(IFF_FFMPEG) { }

      int load_image(me::bytebuff &buffer, me::Image* image, uint64_t flags) override;
      int write_image(me::bytebuff &buffer, me::Image* image, uint64_t flags) override;
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;
      uint64_t supported_flags() override;

    };

  };

};

#endif
