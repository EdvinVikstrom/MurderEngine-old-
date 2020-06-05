#ifndef UI_BUTTON_H
  #define UI_BUTTON_H

#include "ui_element.h"

typedef void (*MEUIButtonFunc) (MeInputEventContext*);

namespace me {

  namespace ui {

    struct button : element {

      bool highlighted;
      MEUIButtonFunc callback;

      button(MeInstance* instance, me::wcolor* color, int posX, int posY, uint32_t scaleX, uint32_t scaleY, MEUIButtonFunc callback) : element(instance, color, posX, posY, scaleX, scaleY)
      {
        highlighted = false;
        this->callback = callback;
      }

      void update() override
      {
      }
      void render() override
      {
      }

      bool mouseEvent(MeInputEventContext* context, int action, double offsetX, double offsetY, int button) override
      {
        if (context->cursorX >= posX && context->cursorX <= posX + scaleX && context->cursorY >= posY && context->cursorY <= posY + scaleY)
        {
          highlighted = true;
          if (action == ME_PRESS)
            callback(context);
        }else
          highlighted = false;
        return false;
      }
      bool keyboardEvent(MeInputEventContext* context, int action, int key) override
      {
        return false;
      }

    };

  };

};

#endif
