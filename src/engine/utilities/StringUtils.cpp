#include <string>
#include <vector>
#include "StringUtils.h"

namespace utils {

  /* !DO NOT FORGET TO DELETE THE ARRAY AFTER USE! */
  std::string* split(const std::string &string, char delimeter, unsigned int& size)
  {
    size = 1; // what if no 'delimeter' found? so start at 1!!!
    for (int i = 0; i < string.size(); i++)
    {
      if (string.at(i)==delimeter)
        size++;
    }
    std::string* array = new std::string[size]; // created on the heap
    unsigned int pos = 0;
    for (int i = 0; i < string.size() && pos < size; i++)
    {
      char c = string.at(i);
      if (c==delimeter)
      {
        pos++;
        continue;
      }
      array[pos]+=c;
    }
    return array;
  }

  std::vector<std::string> lines(const std::string &string)
  {
    std::vector<std::string> lines;
    lines.emplace_back("");
    unsigned int pos = 0;
    for (unsigned int i = 0; i < string.size(); i++)
    {
      if (string.at(i)=='\n')
      {
        lines.emplace_back("");
        pos++;
        continue;
      }
      lines.at(pos)+=string.at(i);
    }
    return lines;
  }

};
