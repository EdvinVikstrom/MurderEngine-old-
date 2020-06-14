#ifndef STRING_U
  #define STRING_U

#include <string>
#include <vector>

namespace me {

  bool str_starts(const std::string &str, const std::string &with);
  bool str_ends(const std::string &str, const std::string &with);
  std::string& upper_case(const std::string &str);
  std::string& lower_case(const std::string &str);
  std::vector<std::string> split_str(const std::string &str, char delimeter);

  bool is_abs_path(const std::string &str);
  std::string to_folder_path(const std::string &str);
  std::string fix_file_path(const std::string &str, bool dir);

  /* very fast functions */
  char** splitf_str(char* data, unsigned int length, unsigned int splits, char delimeter);

};

#endif
