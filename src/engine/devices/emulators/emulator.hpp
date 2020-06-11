#ifndef EMULATOR_H
  #define EMULATOR_H

namespace me {
  
  struct emulator {
    unsigned int mem_size;
    char* mem;
    emulator() { }
    ~emulator()
    {
      delete[] mem;
    }
  };

};

#endif