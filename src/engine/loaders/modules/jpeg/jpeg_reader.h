#ifndef JPEG_READER_H
  #define JPEG_READER_H

#include "../../image_reader.h"

namespace me {

  namespace fformat {

    class jpeg_reader : public image_reader {

    public:

      int read_image(me::fileattr &file, me::image* image) override;
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;

    };

  };

};

#endif
