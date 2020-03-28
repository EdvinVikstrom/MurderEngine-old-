#include <iostream>
#include <string>
#include "Logger.h"
#include "TimeUtils.h"

/* HELPERS */
std::string decodePattern(me::log* log, std::string pattern, me::logMsgType type)
{
  std::string decoded;
  for (int i = 0; i < pattern.size(); i++)
  {
    char c = pattern.at(i);
    bool var = i!=0 && pattern.at(i-1)=='%';
    if (var && c=='N')
      decoded.append(log->prefix);
    else if (var && c=='T')
    {
      unsigned long time = me_utils::getMillis();
      unsigned int seconds = (time / 1000) % 60;
      unsigned int minutes = (time / 1000 / 60) % 60;
      unsigned int hours = (time / 1000 / 60 / 60) % 24;
      decoded.append(std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds));
    }else if (var && c=='D')
      decoded.append("2020/03/18");
    else if (var && c=='M')
      decoded.append("INFO");
    else if (c != '%')
      decoded+=c;
  }
  return decoded;
}

void me::log::out(std::string message)
{
  std::cout << decodePattern(this, me::log::pattern, me::logMsgType::INFO) << message;
}
void me::log::err(std::string message)
{
  std::cout << decodePattern(this, me::log::pattern, me::logMsgType::ERROR) << message;
}
