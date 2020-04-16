#ifndef SCENE_CONTENT_H
  #define SCENE_CONTENT_H

#include <string>
#include <vector>
#include <map>

/* it must be included in this order */
  #include "particle/particle.h"
  #include "texture.h"
  #include "material.h"
  #include "camera.h"
  #include "light.h"
  #include "mesh.h"
  #include "item.h"
/* ------------------------------ */

namespace me {

  struct scene_packet {
    std::map<std::string, me::mesh*> meshes;
    std::map<std::string, me::camera*> cameras;
    std::map<std::string, me::light*> lights;
    std::map<std::string, me::image*> images;
    std::map<std::string, me::material*> materials;
    std::vector<me::item*> items;
  };

};

#endif
