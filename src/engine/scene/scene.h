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
    me::camera* camera;

  public:

    scene(std::string identifier, int x, int y, unsigned int width, unsigned int height);

    virtual void onPreInit(MeInstance* instance);
    virtual void onInit(MeInstance* instance);
    virtual void onDestroyed(MeInstance* instance);

    virtual void onRender(MeRenderer* renderer);
    virtual void onLoop(MeInstance* instance);

    virtual bool onMouseInput(MeInstance* instance, int action, double posX, double posY, int button);
    virtual bool onKeyInput(MeInstance* instance, int action, int key);

  };

};

#endif
