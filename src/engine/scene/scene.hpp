#ifndef SCENE_HPP
  #define SCENE_HPP

#include <vector>

#include "particle/particle.hpp"
#include "texture.hpp"
#include "material.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "mesh.hpp"
#include "item.hpp"

namespace me {

  struct Scene {
    std::vector<me::Image*> images;
    std::vector<me::Material*> materials;
    std::vector<me::Mesh*> meshes;
    std::vector<me::Light*> lights;
    std::vector<me::Camera*> cameras;
  };

};

#endif
