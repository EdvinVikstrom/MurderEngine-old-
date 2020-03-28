#include "rigidbody.h"
#include "../../math/maths.h"

static const me::vec3d CENTER(0, -12, 0);

void me::rigidbody_simulation::applyTo(me::vec3d* position, me::vec3d* rotation)
{
  position->add(velocity);
}

void me::rigidbody_simulation::applyForce(me::vec3d &force)
{
  velocity.add(force);
}

void me::rigidbody_simulation::applyGravity(me::vec3d* position, me::vec3d* rotation)
{
  
}
