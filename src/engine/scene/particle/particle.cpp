#include "particle.h"
#include "../../math/maths.h"

void me::particle::update()
{
  lifeTime++;
}

void me::particle_group::getParticlePos(me::particle* particle, double &x, double &y, double &z)
{
  x = position.x + (maths::cos(particle->random * TAU) * radius);
  y = position.y + (maths::sin(particle->random * TAU) * radius);
  z = position.z + (maths::sin(particle->random * TAU) * radius);
  x = particle->random * 12;
}

void me::particle_group::getParticleRot(me::particle* particle, double &x, double &y, double &z)
{
  x = (maths::cos((double) particle->random * (double) particle->lifeTime) * particle->random * this->radius);
  y = (maths::sin((double) particle->random * (double) particle->lifeTime * 7.456) * particle->random * this->radius);
  z = (maths::sin((double) particle->random * (double) particle->lifeTime * 12.186) * particle->random * this->radius);
}

void me::particle_group::update(unsigned int index, me::particle* particle)
{
  if (particle->lifeTime >= particle->lifeRemaining)
    this->particles.erase(this->particles.begin() + index);
}
