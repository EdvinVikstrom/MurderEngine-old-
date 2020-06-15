#include <iostream>
#include "engine/kernel/common.hpp"
#include "engine/MurderEngine.hpp"

#include "engine/loader/shader_loader.hpp"

/* testing */
  #include "engine/scene/scenes/debug_scene.hpp"
/* ------- */

MeInstance instance;
MeWindow window;
MeCommandBuffer commandBuffer;

int main()
{
  #ifdef DEBUG
    std::cout << "[DEBUG MODE]\n";
  #else
    std::cout << "[RELEASE MODE]\n";
  #endif
  MeInstanceInfo instance_info = {};
  instance_info.appName = "Sandbox";
  instance_info.appVersion = 457;
  meInitInstance(&instance_info, &instance);

  MeWindowInfo window_info = {};
  window_info.title = "Sandbox - MurderEngine";
  window_info.width = 1550;
  window_info.height = 770;
  window_info.posX = 0;
  window_info.posY = 0;
  window_info.monitor = 0;

  MeRendererInfo renderer_info = {};
  renderer_info.api = ME_OPENGL;

  meInitWindow(&instance, &window_info, &window);
  meInitCommandBuffer(&instance, &commandBuffer);
  meInitRenderer(&instance, &renderer_info);

  MeShaders* shaders = new MeShaders;
  me::loadShaders("./src/res/shaders/meshader", *shaders, *instance.renderer);

  instance.scenes.push_back(new me::scene::DebugScene);

  meRunLoop(&instance);

  /* cleanup */
  meDestroyRenderer(instance.renderer);
  meDestroyWindow(&window);
  meDestroyInstance(&instance);
  return 0;
}
