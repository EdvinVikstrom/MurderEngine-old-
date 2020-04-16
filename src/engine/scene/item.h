#ifndef ITEM_H
  #define ITEM_H

#define ME_ITEM_TYPE_MESH          45
#define ME_ITEM_TYPE_LIGHT         46
#define ME_ITEM_TYPE_CAMERA        47
#define ME_ITEM_TYPE_IMAGE         48

namespace me {

  enum item_type {
    NAN,
    MESH,
    LIGHT,
    CAMERA,
    SPRITE
  };

  struct item {
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
    }

    bool onMouseInput(int action, double posX, double posY, int button) { return false; }
    bool onKeyInput(int action, int key) { return false; }

  };

};

#endif
