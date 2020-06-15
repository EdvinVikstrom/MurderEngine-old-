#ifndef KERNEL_HPP
  #define KERNEL_HPP

#include "common.hpp"

namespace me {

  namespace kernel {

    uint64_t mem_use();
    uint64_t mem_available();
    uint64_t mem_pro_use();

    uint32_t cpu_use();
    uint32_t cpu_available();
    uint32_t cpu_pro_use();

  };

};

#endif
