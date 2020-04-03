#include "scene_outliner.h"

void me::scene_outliner::setup()
{
  float aspect = (float)width/(float)height;
  scene::camera = new me::camera("camera", me::camera_type::ORTHOGRAPHIC, aspect, 50, -1, 1);
}

void me::scene_outliner::onRender()
{
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
