#ifndef SIMULATION_H
  #define SIMULATION_H

#define ME_SIMULATION_MODE_ACTIVE             0x1
#define ME_SIMULATION_MODE_PASSIVE            0x2

#define ME_SIMULATION_COLLISION_BOX           0x1
#define ME_SIMULATION_COLLISION_SPHERE        0x2
#define ME_SIMULATION_COLLISION_CONVEX_HULL   0x3
#define ME_SIMULATION_COLLISION_MESH          0x4

#include "../math/vectors.h"
#include "../math/geometry.h"
#include <string>

namespace me {

  namespace sim {

    struct instance {
      me::vec3d* position;
      me::vec3d* rotation;
      me::vec3d* velocity;
      me::gmt::boundary* collisions;
      instance(me::vec3d* position, me::vec3d* rotation, me::vec3d* velocity, me::gmt::boundary* collisions)
      {
        this->position = position;
        this->rotation = rotation;
        this->velocity = velocity;
        this->collisions = collisions;
      }
      ~instance() // *deprecated*
      {
        delete position;
        delete rotation;
        delete velocity;
        delete collisions;
      }
    };

    struct simulation {
      std::string name;
      simulation(std::string name)
      {
        this->name = name;
      }
      ~simulation()
      {

      }
      virtual void applyTo(me::sim::instance* instance) = 0;
      virtual void applyForce(me::sim::instance* instance, me::vec3d &force) = 0;
      virtual void applyGravity(me::sim::instance* instance) = 0;
    };

  };

};

#endif
