#ifndef STRING_UTILS_H
  #define STRING_UTILS_H

#include <vector>

namespace utils {

  std::string* split(const std::string &string, char delimeter, unsigned int& size);
  bool endsWith(const std::string &string, const std::string& with);
  std::vector<std::string> lines(const std::string &string);

};


#endif
