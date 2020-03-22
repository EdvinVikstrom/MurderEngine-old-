#ifndef SCENE_H
  #define SCENE_H


#include <vector>
#include <map>
#include <string>
#include "../math/vectors.h"
#include "../MurderEngine.h"
/* Only include these with scene.h */
#include "texture.h"
#include "shader.h"
#include "material.h"
#include "item.h"
#include "camera.h"
#include "light.h"
#include "mesh.h"

namespace me {

  struct scene_content {
    std::map<std::string, camera*> cameras;
    std::map<std::string, material*> materials;
    std::map<std::string, texture*> textures;
    std::map<std::string, mesh*> meshes;
    std::map<std::string, light*> lights;
  };

  class scene : public me::IEngineEvent {

  private:

    std::string identifier;
    int x, y;
    unsigned int width, height;
    bool _3D;
    unsigned int shader;
    me::camera* camera;

    std::vector<me::item*> items;

  public:

    scene(std::string identifier, int x, int y, unsigned int width, unsigned int height, bool _3D, unsigned int shader);

    void onRender();
    void onLoop();

    void onMouseInput(int action, double posX, double posY, int button);
    void onKeyInput(int action, int key);

    virtual void setup();

    virtual void registerItem(me::item* item);
    virtual void unregisterItem(std::string identifier);
    virtual me::item* getItem(std::string identifier);

  };

};

#endif
