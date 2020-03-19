#ifndef SCENE_H
  #define SCENE_H

#include "../math/vectors.h"
#include "mesh.h"
#include <vector>

namespace me {

  struct item {
    std::string identifier;
    me::mesh* mesh;
    me::vec3d position;
    me::vec3d rotation;
    me::vec3d scale;

    item(std::string identifier, me::mesh* mesh, me::vec3d position, me::vec3d rotation, me::vec3d scale)
    {
      this->identifier = identifier;
      this->mesh = mesh;
      this->position = position;
      this->rotation = rotation;
      this->scale = scale;
    }

    ~item()
    {

    }

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
