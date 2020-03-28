#ifndef SCENE_2D_VIEWPORT_H
  #define SCENE_2D_VIEWPORT_H

#include "../scene.h"

namespace me {

  class scene_2d_viewport : public me::scene {

  public:

    scene_2d_viewport(std::string identifier, int x, int y, unsigned int width, unsigned int height) : scene(identifier, x, y, width, height) { }

    void setup() override;

    void onRender() override;
    void onLoop() override;

    void onMouseInput(int action, double posX, double posY, int button) override;
    void onKeyInput(int action, int key) override;

  };

};

#endif
