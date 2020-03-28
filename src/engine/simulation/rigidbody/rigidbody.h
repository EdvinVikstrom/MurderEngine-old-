#ifndef RIGIDBODY_H
  #define RIGIDBODY_H

#include "../simulation.h"

namespace me {

  struct rigidbody_simulation : me::simulation {

    unsigned char mode; // active or passive
    double mass; // the mass (kg)
    bool dynamic; // true: gravity is applied

    float friction; // range: 0.0F - 1.0F
    float bounciness; // range: 0.0F - 1.0F

    /* object data */
    me::vec3d velocity;
    me::vec3d acceleration;
    
    me::vec3d distance;

    rigidbody_simulation(unsigned char mode, double mass, bool dynamic, float friction, float bounciness) : simulation("RigidBody")
    {
      this->mode = mode;
      this->mass = mass;
      this->dynamic = dynamic;
      this->friction = friction;
      this->bounciness = bounciness;
    }

    void applyTo(me::vec3d* position, me::vec3d* rotation) override;
    void applyForce(me::vec3d &force) override;
    void applyGravity(me::vec3d* position, me::vec3d* rotation) override;

  };

};

#endif
