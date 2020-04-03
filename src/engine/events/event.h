#ifndef EVENT_H
  #define EVENT_H

namespace me {

  namespace event {

    struct event {
      virtual int on_event() = 0;
    };

  };

};

#endif
