#ifndef TAG_TREE_H
  #define TAG_TREE_H

namespace me {

  enum MLValueType : unsigned char {
    NAN,
    UINT8,
    UINT16,
    UINT24,
    UINT32,
    UINT64,

    INT8,
    INT16,
    INT24,
    INT32,
    INT64,

    FLOAT,
    DOUBLE,

    STRING,
    BOOLEAN,

    MARKUP_LANG,
    ML_VALUE
  };

  struct ML_value {
    std::string key;
    ValueType type;
    uint32_t length;
    void* value;
  };

  struct MarkupLang {

    std::map<std::string, ML_value*> tags;

    inline ML_value* pull(std::string key)
    {
      return tags[key];
    }

    inline void push(std::string key, ML_value* value)
    {
      tags[key] = value;
    }

  };

};

#endif
