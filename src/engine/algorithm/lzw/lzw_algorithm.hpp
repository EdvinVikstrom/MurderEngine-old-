#ifndef LZW_COMPRESSION_H
  #define LZW_COMPRESSION_H

#include "../algorithm.hpp"
#include <bits/stdc++.h>

namespace me {

  struct lzw_algorithm : algorithm {

    std::unordered_map<std::string, uint16_t> encodingTable;
    std::unordered_map<uint16_t, std::string> decodingTable;

    lzw_algorithm() : algorithm(ALGORITHM_TYPE_LZW) { }

    void init_encoding_string_table();
    void init_decoding_string_table();

    int decode(me::bytebuff &input, me::bytebuff &output) override;
    int encode(me::bytebuff &input, me::bytebuff &output) override;

  };

};

#endif