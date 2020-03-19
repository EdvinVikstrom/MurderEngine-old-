#include "scene.h"
#include "../renderer/RendererApi.h"

#include <iostream> // remove

extern IRendererApi* rendererApi;

me::scene::scene(std::string identifier, int x, int y, unsigned int width, unsigned int height, bool _3D)
{
  me::scene::identifier = identifier;
  me::scene::x = x;
  me::scene::y = y;
  me::scene::width = width;
  me::scene::height = height;
  me::scene::_3D = _3D;
}

void me::scene::setup()
{
  std::cout << "tjenare\n";
  rendererApi->matrix(ME_MATRIX_PROJECTION);
  rendererApi->viewport(0, 0, width, height);
  float aspect = (float)width/(float)height;
  rendererApi->frustum(-aspect, aspect, -1, 1, 1, 10);
  rendererApi->enable(ME_CULL_FACE);
  rendererApi->cullFace(ME_BACK);
  rendererApi->matrix(ME_MATRIX_MODELVIEW);
}

void me::scene::updateScene()
{

}

void me::scene::renderScene()
{
  for (me::item* item : me::scene::items)
  {
    rendererApi->loadIdentity();
    rendererApi->translated(item->position.x, item->position.y, item->position.z);
    rendererApi->rotated(item->rotation.x, item->rotation.y, item->rotation.z);
    rendererApi->scaled(item->scale.x, item->scale.y, item->scale.z);
    rendererApi->enable(ME_TEXTURE_2D);
    for (me::texture* tex : item->mesh->material->surfaces)
      rendererApi->bind(ME_TEXTURE_2D, tex->image->texId);
    rendererApi->renderMesh(item->mesh);
    rendererApi->disable(ME_TEXTURE_2D);
  }
}
void me::scene::registerItem(me::item* item)
{
  me::scene::items.push_back(item);
}
void me::scene::unregisterItem(std::string identifier)
{
  // TODO:
}
me::item* me::scene::getItem(std::string identifier)
{
  for (me::item* item : me::scene::items)
  {
    if (item->identifier==identifier)
      return item;
  }
  return nullptr;
}
