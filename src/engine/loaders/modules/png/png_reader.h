#ifndef PNG_READER_H
  #define PNG_READER_H

#include "../../image_reader.h"

namespace me {

  namespace fformat {

    enum png_color_type {
      INDEXED,
      GRAYSCALE,
      GRAYSCALE_ALPHA,
      TRUECOLOR,
      TRUECOLOR_ALPHA
    };

    class png_reader : public image_reader {

    public:

      int read_image(me::fileattr &file, me::image* image) override;
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;

    };

  };

};

#endif
