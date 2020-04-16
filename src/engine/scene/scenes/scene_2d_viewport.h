#ifndef SCENE_2D_VIEWPORT_H
  #define SCENE_2D_VIEWPORT_H

#include "../scene.h"

namespace me {

  class scene_2d_viewport : public me::scene {

  public:

    scene_2d_viewport(std::string identifier, int x, int y, unsigned int width, unsigned int height) : scene(identifier, x, y, width, height) { }

    void onPreInit(MeInstance* instance) override;
    void onInit(MeInstance* instance) override;
    void onDestroyed(MeInstance* instance) override;

    void onRender(MeRenderer* renderer) override;
    void onLoop(MeInstance* instance) override;

    bool onMouseInput(MeInstance* instance, int action, double posX, double posY, int button) override;
    bool onKeyInput(MeInstance* instance, int action, int key) override;

  };

};

#endif
