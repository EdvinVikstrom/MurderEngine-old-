#ifndef ME_KERNEL_H
  #define ME_KERNEL_H

#define ME_FINE           0
#define ME_ERR            1

#include <stdint.h>
#include <string>

namespace me {

  struct element {
    std::string identifier;
    std::string value;
  };

};

#endif
