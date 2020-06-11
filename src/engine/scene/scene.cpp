#include "scene.hpp"
#include "../math/maths.hpp"

me::scene::scene(std::string identifier, int x, int y, unsigned int width, unsigned int height)
{
  me::scene::identifier = identifier;
  me::scene::x = x;
  me::scene::y = y;
  me::scene::width = width;
  me::scene::height = height;
}

void me::scene::onPreInit(MeInstance* instance)
{
}

void me::scene::onInit(MeInstance* instance)
{
}

void me::scene::onLoop(MeInstance* instance)
{
}

void me::scene::onRender(MeRenderer* renderer)
{
  renderer->uniformMatrix4(0, camera->projection_matrix);
  renderer->uniformMatrix4(1, camera->view_matrix);
}

bool me::scene::onMouseInput(MeInputEventContext* context, int action, double posX, double posY, int button)
{
  return false;
}
bool me::scene::onKeyInput(MeInputEventContext* context, int action, int key)
{
  return false;
}

void me::scene::onDestroyed(MeInstance* instance)
{
}