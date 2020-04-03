#ifndef SCENE_H
  #define SCENE_H

#include "../kernel/common/common.h"

#include "../events/engine_event.h"
#include "../events/input_event.h"

/* Only include these with scene.h */
  #include "particle/particle.h"
  #include "texture.h"
  #include "material.h"
  #include "camera.h"
  #include "light.h"
  #include "mesh.h"
  #include "item.h"
  #include "ui/ui_element.h"
/* ------------------------------ */

namespace me {

  struct scene_packet {
    std::map<std::string, me::mesh*> meshes;
    std::map<std::string, me::camera*> cameras;
    std::map<std::string, me::light*> lights;
    std::map<std::string, me::wcolor*> images;
    std::map<std::string, me::material*> materials;
    std::vector<me::item*> items;
  };

  class scene : public me::event::engine_event, public me::event::input_event {

  protected:

    std::string identifier;
    int x, y;
    unsigned int width, height;
    me::camera* camera;

    std::vector<me::item*> items;
    std::vector<me::particle_group*> particle_groups;

  public:

    scene(std::string identifier, int x, int y, unsigned int width, unsigned int height);

    virtual void onRender();
    virtual void onLoop();

    virtual bool onMouseInput(int action, double posX, double posY, int button);
    virtual bool onKeyInput(int action, int key);

    virtual void setup();

    void registerItem(me::item* item);
    void unregisterItem(std::string identifier);

  };

};

#endif
