#include "properties.h"

bool me::float_property::validValue(me::data* value)
{
  float a = value->asFloat();
  return a >= range.x && a <= range.y;
}
