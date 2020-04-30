#ifndef ME_NATIVE_H
  #define ME_NATIVE_H

#include "../../script_format.h"

namespace me {

  namespace script {

    struct me_native_script_format : script_format {

      me_native_script_format() : script_format(SFF_MENATIVE) { }

      int compile(me::bytebuff &buffer, me::script::script* script);

    };

  };

};

#endif
