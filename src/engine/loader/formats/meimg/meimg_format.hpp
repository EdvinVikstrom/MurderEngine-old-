#ifndef MEIMG_H
  #define MEIMG_H

#include "../../image_format.hpp"

namespace me {

  namespace format {

    struct meimg_format : image_format {

      meimg_format() : image_format(IFF_MEIMG) { }

      int load_image(me::fileattr &file, me::Image* image) override;
      int write_image(me::bytebuff &buffer, me::Image* image) override;
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;

    };

  };

};

#endif