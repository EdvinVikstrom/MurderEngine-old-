#include "scene_outliner.h"

void me::scene_outliner::setup()
{
  float aspect = (float)width/(float)height;
  scene::camera = new me::camera("camera", {0, 0, 0}, {0, 0, 0}, ME_CAMERA_2D_VIEW, aspect, 50, -1, 1);
}

void me::scene_outliner::onRender()
{
  scene::onRender();
}
void me::scene_outliner::onLoop()
{
  scene::onLoop();
}

void me::scene_outliner::onMouseInput(int action, double posX, double posY, int button)
{
  scene::onMouseInput(action, posX, posY, button);
}
void me::scene_outliner::onKeyInput(int action, int key)
{
  scene::onKeyInput(action, key);
}
