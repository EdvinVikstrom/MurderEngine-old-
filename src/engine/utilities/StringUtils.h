#ifndef STRING_UTILS_H
  #define STRING_UTILS_H

namespace utils {

  std::string* split(std::string string, char delimeter, unsigned int& size);
  bool endsWith(std::string string, std::string with);

};


#endif
