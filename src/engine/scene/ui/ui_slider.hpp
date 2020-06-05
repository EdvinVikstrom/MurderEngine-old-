#ifndef UI_SLIDER_H
  #define UI_SLIDER_H

#include "ui_element.h"

namespace me {

  namespace ui {

    struct slider : element {

      bool vertical;
      double* value;
      double minValue, maxValue;

      slider(MeInstance* instance, int posX, int posY, uint32_t scaleX, uint32_t scaleY, bool vertical, double* value, double minValue, double maxValue) : element(instance, nullptr, posX, posY, scaleX, scaleY)
      {
        this->vertical = vertical;
        this->value = value;
        this->minValue = minValue;
        this->maxValue = maxValue;
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
          double x = me::maths::min(context->cursorX - posX, (double) scaleX);
          double y = me::maths::min(context->cursorY - posY, (double) scaleY);

          double pos = (vertical ? y : x) / (double) (vertical ? scaleY : scaleX);
          double limit = minValue + maxValue;
          double val = pos * limit;
          *value = val - minValue;
        }
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
