#ifndef MURDER_ENGINE
  #define MURDER_ENGINE

#include "kernel/kernel.h"
#include "events/engine_event.h"
#include "events/input_event.h"

namespace me {

  int engine_register_engine_event(me::event::engine_event* event);
  int engine_register_input_event(me::event::input_event* event);
  int engine_init();
  int engine_window(const std::string &title, unsigned int width, unsigned int height, bool vSync, bool fullscreen);
  int engine_loop();
  int engine_load_shaders(const std::string &shader_path);
  int engine_setup_renderer_api(const std::string &apiName, const std::string &shader_filepath);

  void engine_window_size(unsigned int* width, unsigned int* height);

};

#endif
