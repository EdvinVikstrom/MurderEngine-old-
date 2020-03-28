#ifndef SIMULATION_H
  #define SIMULATION_H

#define ME_SIMULATION_MODE_ACTIVE             0x1
#define ME_SIMULATION_MODE_PASSIVE            0x2

#define ME_SIMULATION_COLLISION_BOX           0x1
#define ME_SIMULATION_COLLISION_SPHERE        0x2
#define ME_SIMULATION_COLLISION_CONVEX_HULL   0x3
#define ME_SIMULATION_COLLISION_MESH          0x4

#include "../math/vectors.h"
#include <string>

namespace me {

  struct simulation {
    std::string name;
    simulation(std::string name)
    {
      this->name = name;
    }
    virtual void applyTo(me::vec3d* position, me::vec3d* rotation) = 0;
    virtual void applyForce(me::vec3d &force) = 0;
    virtual void applyGravity(me::vec3d* position, me::vec3d* rotation) = 0;
  };

};

#endif
