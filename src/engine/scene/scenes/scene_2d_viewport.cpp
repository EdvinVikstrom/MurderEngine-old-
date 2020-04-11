#include "scene_2d_viewport.h"
#include "../../loaders/file_format.h"
#include "../../EngineManager.h"

#include <iostream> // remove

static void button_press()
{

}

void me::scene_2d_viewport::setup()
{
  /*
  float aspect = (float)width/(float)height;
  me::transform cam_transform({0, 0, 0}, {0, 0, 0}, {0, 0, 0});
  scene::camera = new me::camera("camera", me::camera_type::PERSPECTIVE, me::maths::to_radians(50.0F), aspect, 0.1F, 100.0F, cam_transform);
  scene::setup();

  me::scene_packet* packet = me::fformat::read_mesh("/home/edvinskomputa/Dokument/OnePunchEngine/src/res/mega test of doom.dae");
  packet->register_all();
  for (me::item* item : packet->items)
  {
    if (item->type != me::item_type::MESH)
      continue;
    scene::registerItem(item);
  }
  */
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
  if (action==ME_MOUSE_SCROLL)
  {
    scene::camera->transform.location.z+=(posY*0.3F);
    scene::camera->update_matrix();
  }else if (action==ME_MOUSE_MOVE && isPressed(ME_MOUSE_MIDDLE_BUTTON))
  {
    scene::camera->transform.rotation.x+=posY*0.0025F;
    scene::camera->transform.rotation.y+=posX*0.0025F;
    scene::camera->update_matrix();
  }
  return scene::onMouseInput(action, posX, posY, button);
}
bool me::scene_2d_viewport::onKeyInput(int action, int key)
{
  return scene::onKeyInput(action, key);
}
