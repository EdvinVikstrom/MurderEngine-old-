#ifndef UI_ELEMENT_H
  #define UI_ELEMENT_H

#include "../../math/transform.h"
#include "../scene.h"

namespace me {

  namespace ui {

    struct ui_element : me::item {

      me::wcolor* texture;

      ui_element(std::string identifier, me::transform transform, me::mesh* mesh, me::wcolor* texture) : item(identifier, me::item_type::SPRITE, transform, mesh)
      {
        this->texture = texture;
      }

      virtual bool onMouseInput(int action, double posX, double posY, int button) = 0;
      virtual bool onKeyInput(int action, int key) = 0;

    };

  };

};

#endif
