#ifndef DEBUG_SCENE_HPP
  #define DEBUG_SCENE_HPP

#include "../../MurderEngine.hpp"

namespace me {

  namespace scene {

    struct DebugScene : MeScene {

      int MeScene_initialize(MeInstance* instance);
      int MeScene_finalize(MeInstance* instance);
      int MeScene_tick(MeInstance* instance);
      int MeScene_render(MeRenderer* renderer, unsigned long current_frame, bool &framebuffer_resized);
      int MeScene_input(MeInstance* instance, MeDeviceType deviceType, uint8_t action, uint8_t keyCode, double x, double y);

    };

  };

};

#endif
