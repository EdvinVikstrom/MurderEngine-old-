#ifndef ALGORITHM_H
  #define ALGORITHM_H

#include "../kernel/io/file_reader.h"

namespace me {

  enum AlgorithmType : unsigned char {
    ALGORITHM_TYPE_LZW,
    ALGORITHM_TYPE_DEFLATE
  };

  struct algorithm {

    AlgorithmType type;

    algorithm(AlgorithmType type)
    {
      this->type = type;
    }

    virtual int decode(me::bytebuff &input, me::bytebuff &output) = 0;
    virtual int encode(me::bytebuff &input, me::bytebuff &output) = 0;

  };

};

#endif
