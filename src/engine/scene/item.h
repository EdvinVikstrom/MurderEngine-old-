#ifndef ITEM_H
  #define ITEM_H

#define ME_ITEM_TYPE_MESH          45
#define ME_ITEM_TYPE_LIGHT         46
#define ME_ITEM_TYPE_CAMERA        47
#define ME_ITEM_TYPE_IMAGE         48

#include "../simulation/simulation.h"
#include "../renderer/renderer_api.h"

extern renderer_api* rendererApi;

namespace me {

  enum item_type {
    NONE,
    MESH,
    LIGHT,
    CAMERA,
    SPRITE
  };

  struct item : me::event::input_event {
    std::string identifier;
    me::item_type type;
    me::transform transform;
    me::mesh* mesh;

    item(std::string identifier, me::item_type type, me::transform transform, me::mesh* mesh)
    {
      this->identifier = identifier;
      this->type = type;
      this->transform = transform;
      this->mesh = mesh;
    }

    item() { }

    ~item()
    {
    }

    virtual void update() { }
    virtual void render()
    {
      rendererApi->transform(transform);
      rendererApi->bindMaterial(mesh->materials->at(0));
      rendererApi->bindMesh(mesh);
      rendererApi->mesh(mesh);
      rendererApi->unbindMesh();
      rendererApi->unbindMaterial();
    }

    bool onMouseInput(int action, double posX, double posY, int button) override { return false; }
    bool onKeyInput(int action, int key) override { return false; }

  };

};

#endif
