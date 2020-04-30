#ifndef USER_INTERFACE_H
  #define USER_INTERFACE_H

#include <string>
#include <map>

#include "ui_element.h"
#include "ui_button.h"
#include "ui_slider.h"

namespace me {

  namespace ui {

    struct user_interface {

      std::map<std::string, element*> elements;

      inline void update(MeInstance* instance)
      {
        for (auto const &[key, value] : elements)
          value->update();
      }

      inline void render(MeRenderer* renderer)
      {
        for (auto const &[key, value] : elements)
          value->render();
      }

      inline bool mouseEvent(MeInputEventContext* context, int action, double offsetX, double offsetY, int button)
      {
        for (auto const &[key, value] : elements)
        {
          if (value->mouseEvent(context, action, offsetX, offsetY, button))
            return true;
        }
        return false;
      }

      inline bool keyboardEvent(MeInputEventContext* context, int action, int key)
      {
        for (auto const &[key1, value] : elements)
        {
          if (value->keyboardEvent(context, action, key))
            return true;
        }
        return false;
      }

    };

  };

};

#endif
