#include "rigidbody.h"

void me::rigidbody_simulation::applyTo(me::vec3d* position, me::vec3d* rotation)
{
  position->add(velocity);
}

void me::rigidbody_simulation::applyForce(me::vec3d direction, float acceleration)
{
  direction.add(mass * acceleration);
  velocity.add(direction);
}
