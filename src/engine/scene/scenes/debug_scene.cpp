#include "debug_scene.hpp"

me::Camera cam;

int me::scene::DebugScene::MeScene_initialize(MeInstance* instance)
{
  uint32_t windowWidth = instance->window->width;
  uint32_t windowHeight = instance->window->height;
  CameraInfo info = {};
  info.projection = me::CameraProjection::PROJ_PERSPECTIVE;
  info.identifier = "testing";
  cam = me::Camera(me::transform(), 50.0F, windowWidth / windowHeight, 0.1F, 100.0F, windowWidth, windowHeight, info);
  return ME_FINE;
}
int me::scene::DebugScene::MeScene_finalize(MeInstance* instance)
{
  return ME_FINE;
}
int me::scene::DebugScene::MeScene_tick(MeInstance* instance)
{
  return ME_FINE;
}
int me::scene::DebugScene::MeScene_render(MeRenderer* renderer, MeFrameBuffer* frameBuffer, unsigned long current_frame, bool &framebuffer_resized)
{
  frameBuffer->useProgram(&renderer->shaders->program_final);
  renderer->uniformMat4x4(frameBuffer->program->locations.projection, cam.projMatrix);
  renderer->uniformMat4x4(frameBuffer->program->locations.view, cam.viewMatrix);
  return ME_FINE;
}
int me::scene::DebugScene::MeScene_input(MeInstance* instance, MeDeviceType deviceType, uint8_t action, uint8_t keyCode, double x, double y)
{
  return ME_FINE;
}
