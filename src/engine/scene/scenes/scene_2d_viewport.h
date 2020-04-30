#ifndef SCENE_2D_VIEWPORT_H
  #define SCENE_2D_VIEWPORT_H

#include "../scene.h"
#include "../ui/user_interface.h"

namespace me {

  class scene_2d_viewport : public me::scene {

  private:

    me::ui::user_interface* ui = new me::ui::user_interface;

  public:

    scene_2d_viewport(std::string identifier, int x, int y, unsigned int width, unsigned int height) : scene(identifier, x, y, width, height) { }

    void onPreInit(MeInstance* instance) override;
    void onInit(MeInstance* instance) override;
    void onDestroyed(MeInstance* instance) override;

    void onRender(MeRenderer* renderer) override;
    void onLoop(MeInstance* instance) override;

    bool onMouseInput(MeInputEventContext* context, int action, double posX, double posY, int button) override;
    bool onKeyInput(MeInputEventContext* context, int action, int key) override;

  };

};

#endif
