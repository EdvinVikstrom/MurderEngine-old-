#ifndef ME_RENDERER_H
  #define ME_RENDERER_H

#include "../scene/scene.h"

namespace me {

  struct ray {
    double distance;
    me::vec4 color;
  };

  void render_scene(me::scene_packet* scene);

};

#endif
