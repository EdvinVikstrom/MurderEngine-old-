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
    me::maths::mat4 transform_matrix;
    me::mesh* mesh;

    item(std::string identifier, me::item_type type, me::maths::mat4 transform_matrix, me::mesh* mesh)
    {
      this->identifier = identifier;
      this->type = type;
      this->transform_matrix = transform_matrix;
      this->mesh = mesh;
    }

    item() { }

    ~item()
    {
    }

    virtual void update() { }
    inline void render(me::camera* camera)
    {
      rendererApi->bindMesh(mesh);
      rendererApi->matrix4(0, camera->projection_matrix.array);
      rendererApi->matrix4(1, camera->view_matrix.array);
      rendererApi->matrix4(2, transform_matrix.array);
      rendererApi->mesh(mesh);
      rendererApi->unbindMesh();
    }

    bool onMouseInput(int action, double posX, double posY, int button) override { return false; }
    bool onKeyInput(int action, int key) override { return false; }

  };

};

#endif
