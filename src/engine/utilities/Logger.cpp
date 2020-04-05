#include <iostream>
#include "../kernel/kernel.h"
#include "Logger.h"
#include "TimeUtils.h"

/* HELPERS */
static const std::string TYPES[4] { "INFO", "WARN", "ERR", "DEBUG" };

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
      decoded.append(TYPES[type]);
    else if (c != '%')
      decoded+=c;
  }
  return decoded;
}

static bool show_info = true;
static bool show_warn = true;
static bool show_err = true;
static bool show_debug = true;

void me::log::out(std::string message)
{
  if (show_info)
    std::cout << decodePattern(this, me::log::out_pattern, me::logMsgType::INFO).c_str() << message.c_str();
}
void me::log::warn(std::string message)
{
  if (show_warn)
    std::cout << decodePattern(this, me::log::warn_pattern, me::logMsgType::WARNING).c_str() << message.c_str();
}
void me::log::err(std::string message)
{
  if (show_err)
    std::cout << decodePattern(this, me::log::err_pattern, me::logMsgType::ERROR).c_str() << message.c_str();
}
void me::log::debug(std::string message)
{
  if (show_debug)
    std::cout << decodePattern(this, me::log::debug_pattern, me::logMsgType::DEBUG).c_str() << message.c_str();
}
