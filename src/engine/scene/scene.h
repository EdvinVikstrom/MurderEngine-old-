#ifndef SCENE_H
  #define SCENE_H


#include <vector>
#include <map>
#include <string>
#include "../math/vectors.h"
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

  class scene {

  private:

    std::string identifier;
    int x, y;
    unsigned int width, height;
    bool _3D;

    std::vector<me::item*> items;

  public:

    scene(std::string identifier, int x, int y, unsigned int width, unsigned int height, bool _3D);

    virtual void setup();

    virtual void updateScene();
    virtual void renderScene();
    virtual void registerItem(me::item* item);
    virtual void unregisterItem(std::string identifier);
    virtual me::item* getItem(std::string identifier);

  };

};

#endif
