#include "scene.h"
#include "../math/maths.h"
#include "../EngineManager.h"
#include "../renderer/renderer_api.h"
#include "../renderer/modules/item_renderer.h"

extern renderer_api* rendererApi;

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
  rendererApi->viewport(me::scene::camera, x, y, width, height);
}

void me::scene::onLoop()
{
}

void me::scene::onRender()
{
  rendererApi->reset();
  for (me::item* i : me::scene::items)
  {
    i->update();
    me::renderer::render_item(i);
  }
}

bool me::scene::onMouseInput(int action, double posX, double posY, int button)
{
  return false;
}
bool me::scene::onKeyInput(int action, int key)
{
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
