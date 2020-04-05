#ifndef ARRAY_UTILS_H
  #define ARRAY_UTILS_H

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
