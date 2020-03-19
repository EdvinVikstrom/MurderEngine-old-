#include <type_traits>
#include <string>
#include <vector>
#include <functional>
#include "StringUtils.h"
#include "ArrayUtils.h"

void utils::processStringArray(const char* strArray, const std::function<void(unsigned int, std::string)>& event)
{
  unsigned int size;
  std::string* args = utils::split(strArray, ' ', size);
  for (int i = 0; i < size; i++)
    event(i, args[i]);
  delete[] args;
}
