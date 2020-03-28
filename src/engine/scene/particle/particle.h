#ifndef PARTICLE_H
  #define PARTICLE_H

#include <vector>
#include "../../math/vectors.h"

namespace me {

  struct particle {

    int properties;
    float random;
    unsigned short lifeTime;
    unsigned short lifeRemaining;

    particle(int properties, int random, unsigned short lifeTime, unsigned short lifeRemaining)
    {
      this->properties = properties;
      this->random = random;
      this->lifeTime = lifeTime;
      this->lifeRemaining = lifeRemaining;
    }

    void update();

    particle() { }

  };

  struct particle_group {

    me::vec3d position;
    me::vec3d velocity;
    double radius;
    unsigned char type;
    bool collisions;
    std::vector<unsigned int> meshes;
    std::vector<particle*> particles;

    particle_group(me::vec3d position, me::vec3d velocity, double radius, unsigned char type, bool collisions)
    {
      this->position = position;
      this->velocity = velocity;
      this->radius = radius;
      this->type = type;
      this->collisions = collisions;
    }

    particle_group() { }

    ~particle_group()
    {
      meshes.clear();
      for (particle* particle : particles)
        delete particle;
      particles.clear();
    }

    /* position */
    void getParticlePos(me::particle* particle, double &x, double &y, double &z);
    /* rotation */
    void getParticleRot(me::particle* particle, double &x, double &y, double &z);

    void update(unsigned int index, me::particle* particle);

  };

};

#endif
