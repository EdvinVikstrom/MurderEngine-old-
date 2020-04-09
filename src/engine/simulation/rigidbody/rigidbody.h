#ifndef RIGIDBODY_H
  #define RIGIDBODY_H

#include "../simulation.h"

namespace me {

  namespace sim {

    struct rigidbody_simulation : me::sim::simulation {

      unsigned char mode; // active or passive
      double mass; // the mass (kg)
      bool dynamic; // true: gravity is applied

      float friction; // range: 0.0F - 1.0F
      float bounciness; // range: 0.0F - 1.0F

      /* object data */
      me::vec3 velocity;
      me::vec3 acceleration;

      me::vec3 distance;

      rigidbody_simulation(unsigned char mode, double mass, bool dynamic, float friction, float bounciness) : simulation("RigidBody")
      {
        this->mode = mode;
        this->mass = mass;
        this->dynamic = dynamic;
        this->friction = friction;
        this->bounciness = bounciness;
      }

      void applyTo(me::sim::instance* instance) override;
      void applyForce(me::sim::instance* instance, me::vec3 &force) override;
      void applyGravity(me::sim::instance* instance) override;

    };

  };

};

#endif
