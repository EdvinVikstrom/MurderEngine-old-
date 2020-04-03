#ifndef UI_BUTTON_H
  #define UI_BUTTON_H

#include "ui_element.h"
#include "../../math/maths.h"
#include <functional>

typedef void (*button_callback)();

namespace me {

  namespace ui {
/*
    struct ui_button : ui_element {

      button_callback callback;

      ui_button(std::string identifier, me::transform transform, me::wcolor color, button_callback callback) : ui_element(identifier, transform, color)
      {
        this->callback = callback;
      }

      bool onMouseInput(int action, double posX, double posY, int button) override
      {
        if (action==ME_PRESS && button==ME_MOUSE_LEFT_BUTTON && maths::inbox(posX, posY, transform.location.x, transform.location.y, transform.scale.x, transform.scale.y))
        {
          callback();
          return true;
        }
        return false;
      }

      bool onKeyInput(int action, int key) override
      {
        return false;
      }

    };
    */

  };

};

#endif
