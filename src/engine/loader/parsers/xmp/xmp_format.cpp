#include "xmp_format.h"

void me::parser::xmp_parser::parse_xmp(const std::string &source, me::MarkupLang &lang)
{
  uint32_t pos = 0;

  bool in_tag = false;
  bool in_attrib = false;
  bool in_string = false;

  std::string current_tag = "";
  std::string current_string = "";

  while(pos < source.size())
  {
    char prev_c = pos > 0 ? source.at(pos-1) : ' ';
    char c = source.at(pos);
    if (!in_string && c == '<')
    {
      in_tag = true;
      continue;
    }else if (!in_string && c == '>')
    {
      in_tag = false;
      continue;
    }else if (!in_string && c == '\"')
    {
      in_string = true;
      continue;
    }else if (in_string && c == '\"' && prev_c != '\\')
    {
      in_string = false;
      continue;
    }

    if (c == ' ' && in_tag && !in_string && !in_attrib)
    {
      in_attrib = true;
      continue;
    }

    if (in_string)
      current_string+=c;
    else if (in_tag && !in_attrib)
      current_tag+=c;

    pos++;
  }
}
