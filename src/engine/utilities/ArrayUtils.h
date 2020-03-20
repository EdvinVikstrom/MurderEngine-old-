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

  template<typename T>
  struct array {
    unsigned int count;
    T* values;
    array(unsigned int count, T* values)
    {
      this->count = count;
      this->values = values;
    }
    array() { }
    ~array()
    {
      delete[] values;
    }
    T at(unsigned int index) // huuuuh &T memory leaks
    {
      return &values[index];
    }
    void erase(unsigned int index)
    {
      values[index] = nullptr;
    }

  };

};

#endif
