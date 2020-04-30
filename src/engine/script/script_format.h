#ifndef SCRIPT_FORMAT_H
  #define SCRIPT_FORMAT_H

namespace me {

  namespace script {

    enum ScriptFileFormat {
      SFF_MENATIVE,
      SFF_CPP,
      SFF_LUA
    };

    struct script_format {

      ScriptFileFormat format;

      script_format(ScriptFileFormat format)
      {
        this->format = format;
      }

      virtual int compile(me::bytebuff &buffer, me::script::script* script) = 0;

    };

  };

};

#endif
