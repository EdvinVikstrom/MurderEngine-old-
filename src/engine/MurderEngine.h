#ifndef MURDER_ENGINE
  #define MURDER_ENGINE

#include "kernel/kernel.h"
#include "events/engine_event.h"
#include "events/input_event.h"

#include <vector>
#include <map>

#define ME_INST_PROGRAM               5
#define ME_INST_RENDERER              7
#define ME_INST_CURRENT_FRAME         8
#define ME_INST_FULLSCREEN            9
#define ME_INST_VSYNC                 14
#define ME_INST_WIN_X                 15
#define ME_INST_WIN_Y                 23
#define ME_INST_WIN_WIDTH             24
#define ME_INST_WIN_HEIGHT            25
#define ME_INST_WINDOW                27
#define ME_INST_WIN_TITLE             28
#define ME_INST_FRAMEBUFFER_RESIZED   31

namespace me {

  void* get_param(int param);
  int set_param(int param, void* value);

  int engine_register_engine_event(me::event::engine_event* event);
  int engine_register_input_event(me::event::input_event* event);
  int engine_init();
  int engine_window(const std::string &title, unsigned int width, unsigned int height, bool vSync, bool fullscreen);
  int engine_loop();
  int engine_load_shaders(const std::string &shader_path);
  int engine_setup_renderer_api(const std::string &apiName, const std::string &shader_filepath);

};

#endif
