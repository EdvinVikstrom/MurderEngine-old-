#include <iostream>
#include "engine/kernel/kernel.h"
#include "engine/MurderEngine.h"

/* sandbox stuff */
#include "engine/scene/scenes/scene_2d_viewport.h"
#include "engine/loaders/modules/glsl/glsl_reader.h"

MeInstance instance;
MeWindow window;
MeCommandBuffer commandBuffer;

static void sandbox()
{
  me::scene_2d_viewport* scene = new me::scene_2d_viewport("en viewport", 0, 0, 1550, 770);
  meRegisterEvent(&instance, scene);
}

int main()
{
  MeInstanceInfo instance_info = {};
  instance_info.appName = "Sandbox";
  instance_info.appVersion = 457;
  meInitInstance(&instance_info, &instance);
  sandbox();

  MeWindowInfo window_info = {};
  window_info.title = "Sandbox - MurderEngine";
  window_info.width = 1550;
  window_info.height = 770;
  window_info.posX = 0;
  window_info.posY = 0;
  window_info.monitor = 0;
  meInitWindow(&instance, &window_info, &window);
  meInitCommandBuffer(&instance, &commandBuffer);
  MeRendererInfo renderer_info = {};
  MeShaderProgram* shaderProgram = new MeShaderProgram;
  me::glsl_reader::read_shader_file("src/res/shaders/shader.glsl", shaderProgram);
  renderer_info.api = ME_OPENGL;
  renderer_info.shaderProgram = shaderProgram;
  meInitRenderer(&instance, &renderer_info);
  meRunLoop(&instance);

  /* cleanup */
  meDestroyRenderer(instance.renderer);
  meDestroyWindow(&window);
  meDestroyInstance(&instance);
  return 0;
}
