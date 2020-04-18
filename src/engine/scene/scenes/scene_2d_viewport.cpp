#include "scene_2d_viewport.h"
#include "../../loader/scene_format.h"
#include "../../loader/image_format.h"
#include "../../loader/file_format.h"

#include <iostream> // remove

static void button_press()
{

}

void me::scene_2d_viewport::onPreInit(MeInstance* instance) { }
void me::scene_2d_viewport::onDestroyed(MeInstance* instance) { }

void me::scene_2d_viewport::onInit(MeInstance* instance)
{
  float aspect = (float)width/(float)height;
  me::vec3 position(0, 0, 0);
  me::vec3 rotation(0.0F, 0.0F, 0.0F);
  scene::camera = new me::Camera("camera", me::CameraProjection::PROJ_PERSPECTIVE, me::maths::to_radians(70.0F), aspect, 0.1F, 100.0F, position, rotation);
  scene::onInit(instance);

  /* reading scene data */
  me::ScenePacket* packet = new me::ScenePacket;
  me::format::loadScene(instance, "/home/edvinskomputa/Dokument/OnePunchEngine/src/res/mega test of doom.dae", packet);

  /* setting up renderer */
  instance->renderer->setupMeshRenderer(instance);
  instance->renderer->setupImageRenderer(instance);
}

void me::scene_2d_viewport::onRender(MeRenderer* renderer)
{
  scene::onRender(renderer);
}
void me::scene_2d_viewport::onLoop(MeInstance* instance)
{
  if (isPressed(instance, ME_KEY_W) || isPressed(instance, ME_KEY_A) || isPressed(instance, ME_KEY_S) || isPressed(instance, ME_KEY_D))
  {
    float speed = 0.5F;
    if (isPressed(instance, ME_KEY_W))
      scene::camera->move(0.0F, 0.0F, -speed);
    if (isPressed(instance, ME_KEY_A))
      scene::camera->move(-speed, 0.0F, 0.0F);
    if (isPressed(instance, ME_KEY_S))
      scene::camera->move(0.0F, 0.0F, speed);
    if (isPressed(instance, ME_KEY_D))
      scene::camera->move(speed, 0.0F, 0.0F);
    scene::camera->update_matrix();
  }
  scene::onLoop(instance);
}

bool me::scene_2d_viewport::onMouseInput(MeInstance* instance, int action, double posX, double posY, int button)
{
  if (action==ME_MOUSE_SCROLL)
  {
    scene::camera->move(0.0F, 0.0F, -((float)posY));
    scene::camera->update_matrix();
  }else if (action==ME_MOUSE_MOVE && isPressed(instance, ME_MOUSE_MIDDLE_BUTTON))
  {
    scene::camera->rotate(posX * 0.005F, posY * 0.005F, 0.0F);
    scene::camera->update_matrix();
  }
  return scene::onMouseInput(instance, action, posX, posY, button);
}
bool me::scene_2d_viewport::onKeyInput(MeInstance* instance, int action, int key)
{
  return scene::onKeyInput(instance, action, key);
}
