#include "properties.h"

bool me::float_property::validValue(float value)
{
  return value >= range.x && value <= range.y;
}

std::vector<float> me::float_property::getValidValues()
{
  return validValues;
}
