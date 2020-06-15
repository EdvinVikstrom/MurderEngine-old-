#ifndef ME_COMMON_HPP
  #define ME_COMMON_HPP

#include <stdint.h>
#include <cstring>

enum MeResult {
  ME_SUCCESS = 0,
  ME_FINE = ME_SUCCESS,
  ME_ERR = 1,
  ME_FILE_CORRUPT = 2,
  ME_FILE_WRONG_TYPE = 3,
  ME_NONE = 5,
  ME_FORMAT_NOT_FOUND = 6
};

#ifdef __cplusplus
  #include "string.hpp"
#endif

#endif
