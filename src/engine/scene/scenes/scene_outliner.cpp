#include "scene_outliner.h"

extern renderer_api* rendererApi;

void me::scene_outliner::setup()
{
  float aspect = (float)width/(float)height;
  me::transform cam_transform({0,0,0},{0,0,0},{0,0,0});
  scene::camera = new me::camera("camera", me::camera_type::VIEW_2D, aspect, 50, -1, 1, width, height, cam_transform);
  rendererApi->viewport(me::scene::camera, x, y, width, height);
  scene::setup();
}

me::wcolor* color = new me::wcolor(me::wcolor_type::RGBA, new me::vec4f(1.0F, 0.4F, 0.2F, 1.0F));
void me::scene_outliner::onRender()
{
  //rendererApi->viewport(me::scene::camera, x, y, width, height);
  rendererApi->reset();
  rendererApi->bindTexture(color);
  rendererApi->quad(0, 0, 120, 120);
  rendererApi->unbindTexture();
  scene::onRender();
}
void me::scene_outliner::onLoop()
{
  scene::onLoop();
}

bool me::scene_outliner::onMouseInput(int action, double posX, double posY, int button)
{
  return scene::onMouseInput(action, posX, posY, button);
}
bool me::scene_outliner::onKeyInput(int action, int key)
{
  return scene::onKeyInput(action, key);
}
