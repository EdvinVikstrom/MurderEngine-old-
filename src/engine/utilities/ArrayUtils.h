#ifndef ARRAY_UTILS_H
  #define ARRAY_UTILS_H

#include <functional>
#include <iostream>

namespace utils {

  class IStrArrayEvent {

  public:

    virtual void onProcess(unsigned int index, std::string arg) = 0;
  };

  void processStringArray(const char* strArray, const std::function<void(unsigned int, std::string)>& event);

};

#endif
