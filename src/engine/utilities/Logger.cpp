#include <iostream>
#include <string>
#include "Logger.h"

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
      decoded.append("11:20:0");
    else if (var && c=='D')
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
