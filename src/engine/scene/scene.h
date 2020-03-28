#ifndef SCENE_H
  #define SCENE_H

#include <vector>
#include <map>
#include <string>
#include "../math/maths.h"
#include "../math/vectors.h"
#include "../MurderEngine.h"

/* Only include these with scene.h */
  #include "item.h"
  #include "particle/particle.h"
  #include "texture.h"
  #include "shader.h"
  #include "material.h"
  #include "camera.h"
  #include "light.h"
  #include "mesh.h"
/* ------------------------------ */

namespace me {

  struct scene_content {
    std::map<std::string, camera*> cameras;
    std::map<std::string, material*> materials;
    std::map<std::string, texture*> textures;
    std::map<std::string, mesh*> meshes;
    std::map<std::string, light*> lights;
  };

  class scene : public me::IEngineEvent {

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

    virtual void onMouseInput(int action, double posX, double posY, int button);
    virtual void onKeyInput(int action, int key);

    virtual void setup();

    void registerItem(me::item* item);
    void unregisterItem(std::string identifier);
    me::item* getItem(std::string identifier);

    void registerParticleGroup(me::particle_group* particle_group);

  };

};

#endif
