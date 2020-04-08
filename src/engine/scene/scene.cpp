#include "scene.h"
#include "../math/maths.h"
#include "../EngineManager.h"
#include "../renderer/renderer_api.h"
#include "../renderer/modules/item_renderer.h"

extern renderer_api* rendererApi;

void me::scene_packet::register_all()
{
  for (auto const &[key, value] : meshes)
    me::registerMesh(value);
  for (auto const &[key, value] : images)
    me::registerImage(value);
}

me::scene::scene(std::string identifier, int x, int y, unsigned int width, unsigned int height)
{
  me::scene::identifier = identifier;
  me::scene::x = x;
  me::scene::y = y;
  me::scene::width = width;
  me::scene::height = height;
}

void me::scene::setup()
{
}

void me::scene::onLoop()
{
}

void me::scene::onRender()
{
  for (me::item* i : me::scene::items)
  {
    rendererApi->reset();
    i->render(camera);
  }
}

bool me::scene::onMouseInput(int action, double posX, double posY, int button)
{
  for (me::item* i : me::scene::items)
  {
    if (i->onMouseInput(action, posX, posY, button))
      return true;
  }
  return false;
}
bool me::scene::onKeyInput(int action, int key)
{
  for (me::item* i : me::scene::items)
  {
    if (i->onKeyInput(action, key))
      return true;
  }
  return false;
}

void me::scene::registerItem(me::item* item)
{
  me::scene::items.push_back(item);
}
void me::scene::unregisterItem(std::string identifier)
{
  // TODO:
}
