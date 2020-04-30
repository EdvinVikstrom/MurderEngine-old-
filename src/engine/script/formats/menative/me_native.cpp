#include "me_native.h"

static void trim(std::string &str)
{
  for (uint32_t i = 0; i < str.size(); i++)
  {
    if (str.at(i) == ' ')
      str.erase(i);
  }
}

static void process_type_var(std::string &source, uint32_t &pos, me::script::script* script)
{
  char sym = source.at(pos++);
  std::string value;
  while(pos < source.size())
  {
    char c = source.at(pos);
    if (c == ';')
    {
      pos++;
      break;
    }
    value+=c;
    pos++;
  }
}

int me::script::me_native::compile(me::bytebuff &buffer, me::script::script* script)
{
  std::string source((const char*) &buffer.data[0], buffer.length);
  trim(source);
  uint32_t pos = 0;
  std::string temp;

  std::string currentType = "nan";

  while(pos < source.size())
  {
    char c = source.at(pos);
    temp+=c;
    if (currentType == "nan" && (c == '=' || c == '+' || c == '-'))
      currentType = "var";
    if (currentType == "var")
    {
      process_type_var(source, pos, script);
    }
    pos++;
  }
  return ME_FINE;
}
