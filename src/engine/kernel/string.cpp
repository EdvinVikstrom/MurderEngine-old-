#include "string.h"
#include "../math/maths.h"
#include <stdio.h>
#include <stdlib.h>

bool me::str_starts(const std::string &str, const std::string &with)
{
  if (str.size() < with.size())
    return false;
  for (unsigned int i = 0; i < with.size(); i++)
  {
    if (str.at(i) != with.at(i))
      return false;
  }
  return true;
}
bool me::str_ends(const std::string &str, const std::string &with)
{
  if (str.size() < with.size())
    return false;
  for (unsigned int i = 0; i < with.size(); i++)
  {
    if (str.at(str.size() - i-1) != with.at(with.size() - i-1))
      return false;
  }
  return true;
}
std::string& me::upper_case(const std::string &str)
{

}
std::string& me::lower_case(const std::string &str)
{

}
std::vector<std::string> me::split_str(std::string &str, char delimeter)
{
  std::vector<std::string> strings;
  unsigned int start = 0, end = 0;
  for (unsigned int i = 0; i < str.size(); i++)
  {
    char &c = str.at(i);
    if (c==delimeter)
    {
      strings.emplace_back(&str.at(start), end);
      start = i + 1;
      end = 0;
      continue;
    }
    end++;
  }
  if (start < str.size())
    strings.emplace_back(&str.at(start));
  return strings;
}

bool me::is_abs_path(const std::string &str)
{
  return str.at(0)=='/' || str.at(0)=='\\' || str.at(1)==':';
}
std::string me::to_folder_path(const std::string &str)
{
  int flast = str.rfind('/');
  int blast = str.rfind('\\');
  int last = flast > blast ? flast : blast;
  if (last < 1)
    return str;
  return str.substr(0, last);
}

/* very fast functions */
char** me::splitf_str(char* data, unsigned int length, unsigned int splits, char delimeter)
{
  char** array = new char*[splits];
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
