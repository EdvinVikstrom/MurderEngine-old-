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

  struct ScenePacket {
    std::map<std::string, me::Mesh*> meshes;
    std::map<std::string, me::Camera*> cameras;
    std::map<std::string, me::Light*> lights;
    std::map<std::string, me::Image*> images;
    std::map<std::string, me::Material*> materials;
    std::vector<me::Item*> items;
  };

};

#endif
