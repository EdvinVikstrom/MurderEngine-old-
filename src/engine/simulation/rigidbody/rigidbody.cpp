#include "rigidbody.h"
#include "../../math/maths.h"

static const me::vec3d CENTER(0, -12, 0);

void me::sim::rigidbody_simulation::applyTo(me::sim::instance* instance)
{
  instance->position->add(velocity);
}

void me::sim::rigidbody_simulation::applyForce(me::sim::instance* instance, me::vec3d &force)
{
  instance->velocity->add(force);
}

void me::sim::rigidbody_simulation::applyGravity(me::sim::instance* instance)
{

}
