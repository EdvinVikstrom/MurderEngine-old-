#include <iostream>
#include "engine/kernel/kernel.h"
#include "engine/MurderEngine.h"
#include "engine/EngineManager.h"

/* sandbox stuff */
#include "engine/scene/scene.h"
#include "engine/scene/scenes/scene_2d_viewport.h"
#include "engine/scene/scenes/scene_outliner.h"
#include "engine/loaders/file_format.h"
#include "engine/simulation/rigidbody/rigidbody.h"

static void sandbox()
{
  me::scene_outliner* scene1 = new me::scene_outliner("en outliner", 0, 0, 350, 770);
  me::scene_2d_viewport* scene2 = new me::scene_2d_viewport("en viewport", 0, 0, 1550, 770);
  //me::engine_register_engine_event(scene1);
  //me::engine_register_input_event(scene1);
  me::engine_register_engine_event(scene2);
  me::engine_register_input_event(scene2);
  //scene1->setup();
  scene2->setup();
}

int main()
{
  if (me::engine_init() != ME_FINE) return 1;
  if (me::engine_window("Murder Engine", 1550, 770, true, false) != ME_FINE) return 1;
  if (me::engine_setup_renderer_api("opengl") != ME_FINE) return 1;
  //if (me::engine_load_shaders("src/res/shaders/shader.glsl") != ME_FINE) return 1;
  me::init();
  sandbox();
  me::engine_loop();
  me::cleanup();
  return 0;
}
