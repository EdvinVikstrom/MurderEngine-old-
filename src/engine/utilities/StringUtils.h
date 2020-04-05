#ifndef STRING_UTILS_H
  #define STRING_UTILS_H

#include <stdbool.h>
#include <string.h>

extern "C" {

  inline unsigned int totalSplits(char* data, unsigned int length, char delimeter)
  {
    unsigned int splits = 1;
    for (unsigned int i = 0; i < length; i++)
    {
      char &c = data[i];
      if (c==delimeter)
        splits++;
    }
    return splits;
  }

  inline char** splitStr(char* data, unsigned int length, unsigned int splits, char delimeter)
  {
    char** array = (char**) malloc(splits * sizeof(char*));
    unsigned int start = 0;
    unsigned int index = 0;
    for (unsigned int i = 0; i < length; i++)
    {
      char &c = data[i];
      if (c==delimeter)
      {
        data[i] = 0;
        array[index] = &data[start];
        start = i + 1;
        index++;
        continue;
      }
    }
    array[splits-1] = &data[start];
    return array;
  }
  inline bool strStartsWith(const char* string, const char* with)
  {
    unsigned int len1 = strlen(string);
    unsigned int len2 = strlen(with);
    for (unsigned int i = 0; i < len1 && i < len2; i++)
    {
      if (with[i] != string[i])
        return false;
    }
    return len2 > 0;
  }
  inline bool strEndsWith(const char* string, const char* with)
  {
    unsigned int len1 = strlen(string);
    unsigned int len2 = strlen(with);
    for (unsigned int i = 0; i < len1 && i < len2; i++)
    {
      if (with[len2-1 - i] != string[len1-1 - i])
        return false;
    }
    return len2 > 0;
  }

};

#endif
