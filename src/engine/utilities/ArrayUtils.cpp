#include <type_traits>
#include <string>
#include <vector>
#include <functional>
#include "StringUtils.h"
#include "ArrayUtils.h"

void me_utils::processStringArray(const std::string &strArray, const std::function<void(unsigned int, std::string)>& event)
{
  std::vector<std::string> args = me_utils::splitStr(strArray, ' ');
  for (int i = 0; i < args.size(); i++)
    event(i, args.at(i));
}

template<typename T>
void me_utils::swap(std::vector<T> array, unsigned int index1, unsigned int index2)
{
  T* temp = &array.at(index2);
  array.at(index2) = array.at(index1);
  array.at(index1) = *temp;
}

template<typename T>
void me_utils::sort(std::vector<T> array, const std::function<int(T, T)> &comparator)
{
  for (unsigned int i = 0; i < array.size()-1; i++)
  {
    int compare = comparator(array.at(0), array.at(1)); // 1: { array[i] > array[i+1] }, { -1: array[i] < array[i+1] }, { 0: array[i] == array[i+1] }
    if (compare > 0)
    {
      me_utils::swap<T>(array, i, i+1);
    }
  }
}
/*

6 3 59 123 15 9 1 4 91 4759 183 92 0 1 2 6 5
3 6

*/
