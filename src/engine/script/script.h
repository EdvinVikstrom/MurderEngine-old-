#ifndef SCRIPT_H
  #define SCRIPT_H

#include <string>
#include <map>

namespace me {

  namespace script {

    enum VarType {
      VAR_INT8,
      VAR_INT16,
      VAR_INT32,
      VAR_INT64,

      VAR_UINT8,
      VAR_UINT16,
      VAR_UINT32,
      VAR_UINT64,

      VAR_FLOAT32,
      VAR_FLOAT64,

      VAR_POINTER

    };

    struct var {
      VarType type;
      uint32_t size;
      void* ptr;
    };

    struct script {

      std::map<std::string, var> vars;

    };

  };

};

#endif
