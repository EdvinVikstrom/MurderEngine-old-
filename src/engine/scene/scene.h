#ifndef SCENE_H
  #define SCENE_H

#include "scene_content.h"
#include "../MurderEngine.h"

namespace me {

  class scene : public MeEngineEvent {

  protected:

    std::string identifier;
    int x, y;
    unsigned int width, height;
    me::Camera* camera;

  public:

    scene(std::string identifier, int x, int y, unsigned int width, unsigned int height);

    virtual void onPreInit(MeInstance* instance);
    virtual void onInit(MeInstance* instance);
    virtual void onDestroyed(MeInstance* instance);

    virtual void onRender(MeRenderer* renderer);
    virtual void onLoop(MeInstance* instance);

    virtual bool onMouseInput(MeInputEventContext* context, int action, double posX, double posY, int button);
    virtual bool onKeyInput(MeInputEventContext* context, int action, int key);

  };

};

#endif
