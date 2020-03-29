#ifndef ARRAY_UTILS_H
  #define ARRAY_UTILS_H

#include <functional>
#include <iostream>
#include <vector>

namespace me_utils {

  class IStrArrayEvent {

  public:

    virtual void onProcess(unsigned int index, std::string arg) = 0;
  };

  void processStringArray(const std::string &strArray, const std::function<void(unsigned int, std::string)> &event);

  template<typename T>
  void swap(std::vector<T> array, unsigned int index1, unsigned int index2);

  template<typename T>
  void sort(std::vector<T> array, const std::function<int(T, T)> &comparator);

};

namespace me {

  template<typename T>
  struct array {
    T* values;
    unsigned int count;
    void allocate_mem(unsigned int count)
    {
      values = new T[count];
      this->count = count;
    }
    void unallocate_mem()
    {
      delete[] values;
      count = 0;
    }
    void put(unsigned int index, T* elements, unsigned int count)
    {
      for (unsigned int i = index; i < count+index; i++)
        values[i] = elements[i-index];
    }
    ~array()
    {
      delete[] values;
    }
  };

};

#endif
