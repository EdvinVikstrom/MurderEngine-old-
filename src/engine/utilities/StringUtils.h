#ifndef STRING_UTILS_H
  #define STRING_UTILS_H

#include <vector>

namespace me_utils {

  inline std::vector<std::string> splitStr(char* string, char delimeter)
  {
    std::vector<std::string> strings;
    strings.emplace_back("");
    unsigned int i = 0;
    while(string[i] != 0)
    {
      char c = string[i];
      if (c==delimeter)
      {
        strings.emplace_back("");
        continue;
      }
      strings.at(strings.size()-1)+=c;
    }
    return strings;
  }
  inline std::vector<std::string> splitStr(const std::string &string, char delimeter)
  {
    return splitStr(string.c_str(), delimeter);
  }
  inline bool strStartsWith(const std::string &string, const std::string& with)
  {
    for (unsigned int i = 0; i < string.size() && i < with.size(); i++)
    {
      if (with.at(i) != string.at(i))
        return false;
    }
    return with.size() > 0;
  }
  inline bool strEndsWith(const std::string &string, const std::string& with)
  {
    for (unsigned int i = 0; i < string.size() && i < with.size(); i++)
    {
      if (with.at(with.size()-1 - i) != string.at(string.size()-1 - i))
        return false;
    }
    return with.size() > 0;
  }

};


#endif
