#ifndef PNG_READER_H
  #define PNG_READER_H

#include "../../image_format.h"

namespace me {

  namespace format {

    enum png_color_type {
      INDEXED,
      GRAYSCALE,
      GRAYSCALE_ALPHA,
      TRUECOLOR,
      TRUECOLOR_ALPHA
    };

    struct png_format : public image_format {

      int read_image(me::fileattr &file, me::Image* image) override;
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;

    };

  };

};

#endif
