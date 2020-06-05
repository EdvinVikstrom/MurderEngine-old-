#ifndef DEFLATE_ALGORITHM_H
  #define DEFLATE_ALGORITHM_H

#include "../algorithm.h"

namespace me {

  struct deflate_algorithm : algorithm {

    deflate_algorithm() : algorithm(ALGORITHM_TYPE_DEFLATE) { }

    int decode(me::bytebuff &input, me::bytebuff &output) override;
    int encode(me::bytebuff &input, me::bytebuff &output) override;

  };

};

#endif
