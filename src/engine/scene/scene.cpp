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
  rendererApi->matrix(ME_MATRIX_PROJECTION);
  rendererApi->viewport(0, 0, width, height);
  float aspect = (float)width/(float)height;
  rendererApi->frustum(-aspect, aspect, -1, 1, 0.1, 100);
  //rendererApi->ortho(-aspect, aspect, -1, 1, -10, 10);
  rendererApi->enable(ME_DEPTH_TEST);
  rendererApi->enable(ME_CULL_FACE);
  rendererApi->cullFace(ME_BACK);
  rendererApi->matrix(ME_MATRIX_MODELVIEW);
}

void me::scene::updateScene()
{

}

double rot = 0;

void me::scene::renderScene()
{
  for (me::item* i : me::scene::items)
  {
    if (i->type != ME_ITEM_TYPE_MESH)
      continue;
    mesh_item* item = (mesh_item*) i;
    rendererApi->loadIdentity();
    rendererApi->translated(item->position->x, item->position->y, item->position->z);
    //rendererApi->rotated(item->rotation->x, item->rotation->y, item->rotation->z);
    rendererApi->scaled(item->scale->x, item->scale->y, item->scale->z);
    rendererApi->rotated(0, rot, 0);
    rendererApi->enable(ME_TEXTURE_2D);
    //rendererApi->bind(ME_TEXTURE_2D, item->mesh->material->rgba.texture->image->texId);
    rendererApi->renderMesh(item->mesh);
    rendererApi->disable(ME_TEXTURE_2D);
    rot+=0.5D;
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
