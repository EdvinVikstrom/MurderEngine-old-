#include "TimeUtils.h"
#include <chrono>

unsigned long me_utils::getMillis()
{
  return std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
}
