#include "scene_outliner.h"

void me::scene_outliner::setup()
{
  scene::setup();
}

void me::scene_outliner::onRender()
{
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
