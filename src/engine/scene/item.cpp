#include <vector>
#include "item.h"

void me::item::update()
{
  for (me::sim::simulation* simulation : simulations)
  {
    simulation->applyGravity(instance);
    simulation->applyTo(instance);
  }
}
