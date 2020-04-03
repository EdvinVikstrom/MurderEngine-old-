#ifndef SIMULATION_H
  #define SIMULATION_H

#define ME_SIMULATION_MODE_ACTIVE             0x1
#define ME_SIMULATION_MODE_PASSIVE            0x2

#define ME_SIMULATION_COLLISION_BOX           0x1
#define ME_SIMULATION_COLLISION_SPHERE        0x2
#define ME_SIMULATION_COLLISION_CONVEX_HULL   0x3
#define ME_SIMULATION_COLLISION_MESH          0x4

#include "../math/transform.h"
#include "../math/geometry.h"
#include "../utilities/mem_utils.h"
#include <string>

namespace me {

  namespace sim {

    struct instance {
      me::transform* transform;
      me::vec3d* velocity;
      me::gmt::boundary* collisions;
      instance(me::transform* transform, me::vec3d* velocity, me::gmt::boundary* collisions)
      {
        this->transform = transform;
        this->velocity = velocity;
        this->collisions = collisions;
      }
      ~instance()
      {
        delete collisions;
      }
    };

    struct simulation : mem_utils {
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

      long mem_use() override
      {
        return name.size();
      }

    };

  };

};

#endif
