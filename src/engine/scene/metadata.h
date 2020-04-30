#ifndef METADATA_H
  #define METADATA_H

#include <string>
#include <map>

namespace me {

  struct metadata {

    enum TagType : uint16_t {
      MTT_NAN = 0x0000,
      MTT_UINT8 = 0x0101,
      MTT_UINT16 = 0x0202,
      MTT_UINT24 = 0x0303,
      MTT_UINT32 = 0x0404,
      MTT_UINT64 = 0x0508,
      MTT_URATIONAL = 0x0610,
      MTT_INT8 = 0x0701,
      MTT_INT16 = 0x0802,
      MTT_INT24 = 0x0903,
      MTT_INT32 = 0x0A04,
      MTT_INT64 = 0x0B08,
      MTT_FLOAT32 = 0x0C04,
      MTT_FLOAT64 = 0x0D08,
      MTT_RATIONAL = 0x0E10,
      MTT_STRING = 0x0F00,
      MTT_ARRAY = 0x1000
    };

    struct Tag {
      std::string key;
      TagType type;
      uint32_t length;
      uint8_t* value;

      Tag(std::string key, TagType type, uint32_t length, uint8_t* value)
      {
        this->key = key;
        this->type = type;
        this->length = length;
        this->value = value;
      }

    };

    std::map<std::string, Tag*> tags;

    inline Tag* getTag(std::string key)
    {
      if (!tags.count(key))
        return nullptr;
      return tags[key];
    }

    inline void putTag(Tag* tag)
    {
      tags[tag->key] = tag;
    }

  };

};

#endif
