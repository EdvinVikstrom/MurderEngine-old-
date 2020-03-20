#include "maths.h"
#include <cstdlib>

double maths::rand()
{
  return ((double) rand() / RAND_MAX) + 1;
}
