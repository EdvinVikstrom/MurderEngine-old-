#include "scene_2d_viewport.h"
#include "../../renderer/renderer_api.h"
#include "../../loaders/file_format.h"
#include "../../EngineManager.h"

#include "../ui/ui_button.h"

extern renderer_api* rendererApi;

static void button_press()
{

}

void me::scene_2d_viewport::setup()
{
  float aspect = (float)width/(float)height;
  me::scene_packet* packet = me::fformat::read_mesh("/home/edvinskomputa/Dokument/OnePunchEngine/src/res/sprite.dae");
  // register all with EngineManager
  for (me::item* item : packet->items)
    registerItem(item);
  delete packet;
  scene::setup();
}

void me::scene_2d_viewport::onRender()
{
  scene::onRender();
}
void me::scene_2d_viewport::onLoop()
{
  scene::onLoop();
}

bool me::scene_2d_viewport::onMouseInput(int action, double posX, double posY, int button)
{
  return scene::onMouseInput(action, posX, posY, button);
}
bool me::scene_2d_viewport::onKeyInput(int action, int key)
{
  return scene::onKeyInput(action, key);
}
