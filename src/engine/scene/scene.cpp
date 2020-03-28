#include "scene.h"
#include "../math/maths.h"
#include "../EngineManager.h"
#include "../renderer/renderer_api.h"

#include <iostream> // remove

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
}

void me::scene::onLoop()
{
}

void me::scene::onRender()
{
  for (me::item* i : me::scene::items)
  {
    if (i->type == ME_ITEM_TYPE_MESH)
    {
      me::mesh_item* item = (mesh_item*) i;
      me::mesh* mesh = me::getMesh(item->mesh);
      rendererApi->push();
      rendererApi->reset();

      /* camera */
      rendererApi->translate(me::scene::camera->position.x, me::scene::camera->position.y, me::scene::camera->position.z, 0);
      rendererApi->rotate(me::scene::camera->rotation.x, me::scene::camera->rotation.y, me::scene::camera->rotation.z, 0);

      rendererApi->translate(item->position.x, item->position.y, item->position.z, 0);
      rendererApi->rotate(item->rotation.x, item->rotation.y, item->rotation.z, 0);
      rendererApi->scale(item->scale.x, item->scale.y, item->scale.z, 0);

      me::material* material = me::getMaterial(mesh->material);

      material->rgba->bind();
      rendererApi->bindMesh(mesh);
      rendererApi->mesh(mesh);
      rendererApi->unbindMesh();
      material->rgba->unbind();

      rendererApi->pop();
    }else if (i->type == ME_ITEM_TYPE_IMAGE)
    {
      image_item* item = (image_item*) i;
      rendererApi->push();
      rendererApi->reset();

      /* camera */
      rendererApi->translate(me::scene::camera->position.x, me::scene::camera->position.y, me::scene::camera->position.z, 0);
      rendererApi->rotate(me::scene::camera->rotation.x, me::scene::camera->rotation.y, me::scene::camera->rotation.z, 0);

      rendererApi->bindImage(me::getImage(item->image));
      rendererApi->plane(item->position.x, item->position.y, item->scale.x, item->scale.y);
      rendererApi->unbindImage();

      rendererApi->pop();
    }
  }
  for (me::particle_group* group : me::scene::particle_groups)
  {
    rendererApi->push();

    me::mesh* mesh = me::getMesh(group->meshes.at((unsigned int) maths::rand() * group->meshes.size()));

    me::material* material = me::getMaterial(mesh->material);
    material->rgba->bind();
    rendererApi->bindMesh(mesh);

    for (unsigned int i = 0; i < group->particles.size(); i++)
    {
      me::particle* particle = group->particles.at(i);
      double posX, posY, posZ;
      double rotX, rotY, rotZ;

      group->getParticlePos(particle, posX, posY, posZ);
      group->getParticleRot(particle, rotX, rotY, rotZ);

      rendererApi->reset();

      /* camera */
      rendererApi->translate(me::scene::camera->position.x, me::scene::camera->position.y, me::scene::camera->position.z, 0);
      rendererApi->rotate(me::scene::camera->rotation.x, me::scene::camera->rotation.y, me::scene::camera->rotation.z, 0);

      rendererApi->translate(posX, posY, posZ, 0);
      rendererApi->rotate(rotX, rotY, rotZ, 0);
      rendererApi->scale(1, 1, 1, 0);

      rendererApi->mesh(mesh);

      particle->update();
      group->update(i, particle);
    }
    material->rgba->unbind();
    rendererApi->unbindMesh();
    rendererApi->pop();
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

void me::scene::registerParticleGroup(me::particle_group* particle_group)
{
  me::scene::particle_groups.push_back(particle_group);
}
