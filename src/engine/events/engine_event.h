#ifndef ENGINE_EVENT_H
  #define ENGINE_EVENT_H

namespace me {

  namespace event {

    struct engine_event {

      virtual void onRender() = 0;
      virtual void onLoop() = 0;

    };

  };

};

#endif
