#ifndef UI_ELEMENT_H
  #define UI_ELEMENT_H

static std::vector<me::vertex> RECT_VERTICIES = {
  { {0.0F, 0.0F, 0.0F}, {0.0F, 0.0F, 0.0F}, {0.0F, 0.0F}, {0.0F, 0.0F, 0.0F, 0.0F} },
  { {1.0F, 0.0F, 0.0F}, {0.0F, 0.0F, 0.0F}, {1.0F, 0.0F}, {0.0F, 0.0F, 0.0F, 0.0F} },
  { {0.0F, 1.0F, 0.0F}, {0.0F, 0.0F, 0.0F}, {0.0F, 1.0F}, {0.0F, 0.0F, 0.0F, 0.0F} },
  { {1.0F, 1.0F, 0.0F}, {0.0F, 0.0F, 0.0F}, {1.0F, 1.0F}, {0.0F, 0.0F, 0.0F, 0.0F} }
};

static std::vector<unsigned int> RECT_INDICES = {
  0, 1, 2,
  1, 3, 2
};

namespace me {

  namespace ui {

    struct element {

      me::wcolor* color;
      int posX, posY;
      uint32_t scaleX, scaleY;

      element(MeInstance* instance, me::wcolor* color, int posX, int posY, uint32_t scaleX, uint32_t scaleY)
      {
        this->color = color;
        this->posX = posX;
        this->posY = posY;
        this->scaleX = scaleX;
        this->scaleY = scaleY;
        if (color != nullptr)
        {
          me::Mesh* mesh = new me::Mesh;
          //mesh->identifier = "ui-mesh";
          mesh->vertices = RECT_VERTICIES;
          mesh->indices = RECT_INDICES;
          mesh->transform = me::transform({posX, posY, 0}, {0, 0, 0}, {scaleX, scaleY, 1});
          mesh->materials.push_back(new me::Material("ui-material", color));
          //instance->loadMesh(mesh);
        }
      }

      virtual void update() = 0;
      virtual void render() = 0;

      virtual bool mouseEvent(MeInputEventContext* context, int action, double offsetX, double offsetY, int button) = 0;
      virtual bool keyboardEvent(MeInputEventContext* context, int action, int key) = 0;

    };

  };

};

#endif
