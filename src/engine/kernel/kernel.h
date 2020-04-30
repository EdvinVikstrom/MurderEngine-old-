#ifndef ME_KERNEL_H
  #define ME_KERNEL_H

#ifndef ME_UINT_32_BIT
  #define ME_UINT_32_BIT
#endif

enum MeResult {
  ME_SUCCESS = 0,
  ME_FINE = ME_SUCCESS,
  ME_ERR = 1,
  ME_FILE_CORRUPT = 2,
  ME_FILE_WRONG_TYPE = 3,
  ME_NONE = 5
};

enum MeBool {
  ME_TRUE = 1,
  ME_FALSE = 0
};

#define ME_DEBUG

#ifdef ME_UINT_32_BIT
  #define _uint_t unsigned int
#elif ME_UINT_16_BIT
  #define _uint_t unsigned short
#elif ME_UINT_8_BIT
  #define _uint_t unsigned char
#elif ME_UINT_64_BIT
  #define _uint_t unsigned long
#endif

#include <stdint.h>
#include <cstring>

#ifdef __cplusplus
  #include "string.h"
#endif

#endif
