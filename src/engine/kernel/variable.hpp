#ifndef VARIABLE_HPP
  #define VARIABLE_HPP

namespace me {

  enum VarType {
    VAR_INT8, VAR_INT16, VAR_INT32, VAR_INT64,
    VAR_UINT8, VAR_UINT16, VAR_UINT32, VAR_UINT64,
    VAR_FLOAT32, VAR_FLOAT64,
    VAR_VEC2I, VAR_VEC2F,
    VAR_VEC3I, VAR_VEC3F,
    VAR_VEC4I, VAR_VEC4F,
    VAR_STRING,
    VAR_BYTE_ARRAY
  };

  template<typename T>
  struct Var {
    VarType type;
    uint32_t size;
    T value;

    Var(VarType type, uint32_t size, T value)
    {
      this->type = type;
      this->size = size;
      this->value = value;
    }

  };

};

#endif
