#ifndef NES_EMULATOR_H
  #define NES_EMULATOR_H

#include "emulator.hpp"

namespace me {

  namespace emulator_nes {

    struct NES {
      unsigned int
    };

    void init(me::emulator* emulator);
    void loadROM(char* data, unsigned int size);

  };

};

#endif