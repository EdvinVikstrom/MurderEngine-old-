#ifndef ME_READER_H
  #define ME_READER_H

#include "../../file_format.h"

namespace me {

  namespace fformat {

    class me_reader : public file_format {

    public:

      void read_file(const std::string &filepath);

      bool recognized(me::file_state &file) override;
      std::vector<std::string> get_file_exts() override;

    };

  };

};

#endif
