#include <vector>
#include "item.h"

void me::item::update()
{
  for (me::simulation* simulation : simulations)
    simulation->applyTo(&position, &rotation);
}
