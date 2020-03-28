#ifndef SCENE_OUTLINER_H
  #define SCENE_OUTLINER_H

#include "../scene.h"

namespace me {

  class scene_outliner : public me::scene {

  public:

    scene_outliner(std::string identifier, int x, int y, unsigned int width, unsigned int height) : scene(identifier, x, y, width, height) { }

    void setup() override;

    void onRender() override;
    void onLoop() override;

    void onMouseInput(int action, double posX, double posY, int button) override;
    void onKeyInput(int action, int key) override;

  };

};

#endif
