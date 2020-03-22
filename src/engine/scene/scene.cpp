#include "scene.h"
#include "../renderer/RendererApi.h"

#include <iostream> // remove

extern IRendererApi* rendererApi;

me::scene::scene(std::string identifier, int x, int y, unsigned int width, unsigned int height, bool _3D, unsigned int shader)
{
  me::scene::identifier = identifier;
  me::scene::x = x;
  me::scene::y = y;
  me::scene::width = width;
  me::scene::height = height;
  me::scene::_3D = _3D;
  me::scene::shader = shader;
}

void me::scene::setup()
{
  rendererApi->matrix(ME_MATRIX_PROJECTION);
  rendererApi->viewport(0, 0, width, height);
  float aspect = (float)width/(float)height;
  me::scene::camera = new me::camera("camera", {0, 0, 0}, {0, 0, 0}, ME_CAMERA_PERSPECTIVE, aspect, 50, 0.1, 1000);
  rendererApi->perspective(me::scene::camera->focalLength, me::scene::camera->aspectRatio, me::scene::camera->znear, me::scene::camera->zfar);
  rendererApi->enable(ME_DEPTH_TEST);
  rendererApi->enable(ME_CULL_FACE);
  rendererApi->cullFace(ME_BACK);
  rendererApi->matrix(ME_MATRIX_MODELVIEW);
  rendererApi->useAlpha(true);
  //rendererApi->shader(me::scene::shader);
}

void me::scene::onLoop()
{
  if (isPressed(ME_KEY_W))
    me::scene::camera->position.z+=0.1D;
  if (isPressed(ME_KEY_A))
    me::scene::camera->position.x-=0.1D;
  if (isPressed(ME_KEY_S))
    me::scene::camera->position.z-=0.1D;
  if (isPressed(ME_KEY_D))
    me::scene::camera->position.x+=0.1D;
}

me::vec4f red(1.0F, 0.0F, 0.0F, 0.6F);
me::vec4f blue(0.0F, 0.0F, 1.0F, 0.6F);
me::vec4f gray(0.2F, 0.2F, 0.2F, 0.6F);
me::vec3d fromX(-1000, 0, 0);
me::vec3d toX(1000, 0, 0);
me::vec3d fromZ(0, 0, -1000);
me::vec3d toZ(0, 0, 1000);

int gridSize = 2;
int gridLength = 1000;

void me::scene::onRender()
{
  rendererApi->loadIdentity();
  rendererApi->translated(me::scene::camera->position);
  rendererApi->rotated(me::scene::camera->rotation);
  rendererApi->line(red, fromX, toX);
  rendererApi->line(blue, fromZ, toZ);
  for (int x = -gridLength; x < gridLength; x+=gridSize)
  {
    me::vec3d from(x, 0, -gridLength);
    me::vec3d to(x, 0, gridLength);
    rendererApi->line(gray, from, to);
  }
  for (int z = -gridLength; z < gridLength; z+=gridSize)
  {
    me::vec3d from(-gridLength, 0, z);
    me::vec3d to(gridLength, 0, z);
    rendererApi->line(gray, from, to);
  }
  for (me::item* i : me::scene::items)
  {
    if (i->type != ME_ITEM_TYPE_MESH)
      continue;
    mesh_item* item = (mesh_item*) i;
    rendererApi->pushMatrix();
    rendererApi->loadIdentity();

    rendererApi->translated(me::scene::camera->position);
    rendererApi->rotated(me::scene::camera->rotation);
    rendererApi->translated(item->position->x, item->position->y, item->position->z);

    rendererApi->rotated(item->rotation->x, item->rotation->y, item->rotation->z);
    rendererApi->scaled(item->scale->x, item->scale->y, item->scale->z);


    rendererApi->enable(ME_TEXTURE_2D);
    rendererApi->bind(ME_TEXTURE_2D, item->mesh->material->rgba->image->texId);
    //std::cout << item->mesh->material->rgba->image << "\n";
    rendererApi->renderMesh(item->mesh);
    rendererApi->disable(ME_TEXTURE_2D);
    rendererApi->popMatrix();
  }
}

float rotationSensitivity = 0.25F;
float moveSensitivity = 0.025F;
void me::scene::onMouseInput(int action, double posX, double posY, int button)
{
  if (action==ME_MOUSE_MOVE && isPressed(ME_MOUSE_MIDDLE_BUTTON))
  {
    if (isPressed(ME_KEY_LEFT_SHIFT))
    {
      me::scene::camera->position.x+=(posX*moveSensitivity);
      me::scene::camera->position.y-=(posY*moveSensitivity);
    }else
    {
      me::scene::camera->rotation.y+=(posX*rotationSensitivity);
      me::scene::camera->rotation.x+=(posY*rotationSensitivity);
    }
  }else if (action==ME_MOUSE_SCROLL)
  {
    me::scene::camera->position.z+=posY;
  }
}
void me::scene::onKeyInput(int action, int key)
{
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
