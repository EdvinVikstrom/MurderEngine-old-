#include <vector>
#include "item.h"

void me::item::update()
{
  for (me::simulation* simulation : simulations)
  {
    simulation->applyGravity(&position, &rotation);
    simulation->applyTo(&position, &rotation);
  }
}
