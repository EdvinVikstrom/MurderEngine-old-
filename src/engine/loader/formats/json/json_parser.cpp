#include "json_parser.h"

int me::parser::json_parser::parse_json(me::fileattr &file, json_tree* tree)
{
  file.readFile();
  unsigned char* data = file.buffer->data;
  json_tree* current_tree = nullptr;
  for (uint32_t i = 0; i < file.buffer->length; i++)
  {
    unsigned char c = data[i];
    switch(c)
    {
      case '{':
      
      break;
    }
  }
  return ME_FINE;
}
