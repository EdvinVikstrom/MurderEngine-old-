#ifndef PROPERTIES_H
  #define PROPERTIES_H

#define ME_DATA_TYPE_BYTES                    0x1
#define ME_DATA_TYPE_STRING                   0x2
#define ME_DATA_TYPE_SHORT                    0x3
#define ME_DATA_TYPE_INT                      0x4
#define ME_DATA_TYPE_LONG                     0x5
#define ME_DATA_TYPE_UNSIGNED_SHORT           0x6
#define ME_DATA_TYPE_UNSIGNED_INT             0x7
#define ME_DATA_TYPE_UNSIGNED_LONG            0x8
#define ME_DATA_TYPE_FLOAT                    0x9
#define ME_DATA_TYPE_DOUBLE                   0xA
#define ME_DATA_TYPE_LONG_DOUBLE              0xB
#define ME_DATA_TYPE_BOOLEAN                  0xC

#include <string>
#include <vector>
#include <map>
#include "../math/vectors.h"
#include "ArrayUtils.h"

namespace me {

  struct data { // TODO: [int to char*] "bytes" points to stack ?
    unsigned char type;
    char* bytes;
    unsigned int length;
    data(unsigned char type, char* bytes, unsigned int length)
    {
      this->type = type;
      this->bytes = bytes;
      this->length = length;
      type = ME_DATA_TYPE_BYTES;
    }
    data(const char* string)
    {
      /* getting the length of the string */
      do {
        length++;
      }while(string[length] != 0);
      bytes = (char*) string;
      type = ME_DATA_TYPE_STRING;
    }
    data(const std::string &string)
    {
      length = string.size();
      bytes = (char*) string.c_str();
      type = ME_DATA_TYPE_STRING;
    }
    data(short s)
    {
      length = sizeof(s);
      bytes = (char*) &s; // *C-style cast*
      type = ME_DATA_TYPE_SHORT;
    }
    data(int i)
    {
      length = sizeof(i);
      bytes = (char*) &i; // *C-style cast*
      type = ME_DATA_TYPE_INT;
    }
    data(long l)
    {
      length = sizeof(l);
      bytes = (char*) &l; // *C-style cast*
      type = ME_DATA_TYPE_LONG;
    }
    data(unsigned short s)
    {
      length = sizeof(s);
      bytes = (char*) &s; // *C-style cast*
      type = ME_DATA_TYPE_UNSIGNED_SHORT;
    }
    data(unsigned int i)
    {
      length = sizeof(i);
      bytes = (char*) &i; // *C-style cast*
      type = ME_DATA_TYPE_UNSIGNED_INT;
    }
    data(unsigned long l)
    {
      length = sizeof(l);
      bytes = (char*) &l; // *C-style cast*
      type = ME_DATA_TYPE_UNSIGNED_LONG;
    }
    data(float f)
    {
      length = sizeof(f);
      bytes = (char*) &f; // *C-style cast*
      type = ME_DATA_TYPE_FLOAT;
    }
    data(double d)
    {
      length = sizeof(d);
      bytes = (char*) &d; // *C-style cast*
      type = ME_DATA_TYPE_DOUBLE;
    }
    data(long double d)
    {
      length = sizeof(d);
      bytes = (char*) &d; // *C-style cast*
      type = ME_DATA_TYPE_LONG_DOUBLE;
    }
    data(bool b)
    {
      length = 1;
      bytes = new char[length] { b ? (char) 1 : (char) 0 };
      type = ME_DATA_TYPE_BOOLEAN;
    }
    ~data()
    {
      delete[] bytes;
    }

    short asShort()
    {
      return *((short*) &bytes[0]);
    }
    short asInt()
    {
      return *((int*) &bytes[0]);
    }
    short asLong()
    {
      return *((long*) &bytes[0]);
    }
    short asUnsignedShort()
    {
      return *((unsigned short*) &bytes[0]);
    }
    short asUnsignedInt()
    {
      return *((unsigned int*) &bytes[0]);
    }
    short asUnsignedLong()
    {
      return *((unsigned long*) &bytes[0]);
    }
    short asFloat()
    {
      return *((float*) &bytes[0]);
    }
    short asDouble()
    {
      return *((double*) &bytes[0]);
    }
    short asLongDouble()
    {
      return *((long double*) &bytes[0]);
    }
    short asBoolean()
    {
      return bytes[0] == 1;
    }

  };

  struct property {
    std::string identifier;
    me::data* value;
    std::vector<me::data> validValues;

    property(std::string identifier, me::data* value)
    {
      this->identifier = identifier;
      this->value = value;
    }

    property() { }

    ~property()
    {

    }

    virtual bool validValue(me::data* value) = 0;
    virtual std::vector<me::data> getValidValues()
    {
      return validValues;
    }
  };

  struct property_list {
    /* param[0]: the category | param[1]: the property */
    std::map<std::string, me::property*> properties;

    ~property_list()
    {
      properties.clear();
    }

  };

  struct float_property : property {
    me::vec2f range;
    float_property(std::string identifier, float value, me::vec2f range) : property(identifier, new data(value))
    {
      this->range = range;
    }
    bool validValue(me::data* value) override;
  };

};

#endif
