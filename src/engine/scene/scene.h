#ifndef SCENE_H
  #define SCENE_H

#include "../math/vectors.h"
#include "mesh.h"
#include "camera.h"
#include "material.h"
#include "texture.h"
#include "light.h"
#include <vector>

namespace me {

  struct item {
    std::string identifier;
    me::vec3d position;
    me::vec3d rotation;
    me::vec3d scale;

    ~item() { }

  };

  struct scene_content {
    std::vector<camera*> cameras;
    std::vector<material*> materials;
    std::vector<texture*> textures;
    std::vector<mesh*> meshes;
    std::vector<light*> lights;
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
