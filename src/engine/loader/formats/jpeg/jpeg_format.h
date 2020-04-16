#ifndef JPEG_READER_H
  #define JPEG_READER_H

#include "../../image_format.h"

namespace me {

  namespace format {

    struct jpeg_format : public image_format {

      int read_image(me::fileattr &file, me::image* image) override;
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;

    };

  };

};

#endif
