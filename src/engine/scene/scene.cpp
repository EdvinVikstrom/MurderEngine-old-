#include "scene.h"
#include "../renderer/RendererApi.h"

extern IRendererApi* RENDERER_API;

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
  RENDERER_API->matrix(ME_MATRIX_PROJECTION);
  RENDERER_API->viewport(0, 0, width, height);
  float aspect = (float)width/(float)height;
  RENDERER_API->frustum(-aspect, aspect, -1, 1, 1, 10);
  RENDERER_API->enable(ME_CULL_FACE);
  RENDERER_API->cullFace(ME_BACK);
  RENDERER_API->matrix(ME_MATRIX_MODELVIEW);
}

void me::scene::updateScene()
{
  
}

void me::scene::renderScene()
{
  for (me::item* item : me::scene::items)
  {
    RENDERER_API->loadIdentity();
    RENDERER_API->translated(item->position.x, item->position.y, item->position.z);
    RENDERER_API->rotated(item->rotation.x, item->rotation.y, item->rotation.z);
    RENDERER_API->scaled(item->scale.x, item->scale.y, item->scale.z);
    RENDERER_API->enable(ME_RENDERER_TEXTURE_2D);
    RENDERER_API->bind(ME_RENDERER_TEXTURE_2D, item->mesh->material->surfaces)
    for (me::texture* tex : item->mesh->material->surfaces)
      RENDERER_API->bind(ME_RENDERER_TEXTURE_2D, tex->image->texId);
    RENDERER_API->renderMesh(item->mesh);
    RENDERER_API->disable(ME_RENDERER_TEXTURE_2D);
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
