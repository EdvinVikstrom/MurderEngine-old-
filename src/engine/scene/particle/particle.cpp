#include "particle.h"
#include "../../math/maths.h"

void me::particle::update()
{
  lifeTime++;
}

void me::particle_group::getParticlePos(me::particle* particle, double &x, double &y, double &z)
{
  x = position.x + (maths::cosd(particle->random * TAU) * radius);
  y = position.y + (maths::sind(particle->random * TAU) * radius);
  z = position.z + (maths::sind(particle->random * TAU) * radius);
  x = particle->random * 12;
}

void me::particle_group::getParticleRot(me::particle* particle, double &x, double &y, double &z)
{
  x = (maths::cosd((double) particle->random * (double) particle->lifeTime) * particle->random * this->radius);
  y = (maths::sind((double) particle->random * (double) particle->lifeTime * 7.456) * particle->random * this->radius);
  z = (maths::sind((double) particle->random * (double) particle->lifeTime * 12.186) * particle->random * this->radius);
}

void me::particle_group::update(unsigned int index, me::particle* particle)
{
  if (particle->lifeTime >= particle->lifeRemaining)
    this->particles.erase(this->particles.begin() + index);
}
