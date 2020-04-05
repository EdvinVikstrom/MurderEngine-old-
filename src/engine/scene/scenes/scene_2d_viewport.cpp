#include "scene_2d_viewport.h"
#include "../../renderer/renderer_api.h"
#include "../../loaders/file_format.h"
#include "../../EngineManager.h"

#include "../ui/ui_button.h"

#include <iostream> // remove

extern renderer_api* rendererApi;

static void button_press()
{

}

void me::scene_2d_viewport::setup()
{
  float aspect = (float)width/(float)height;
  me::transform cam_transform({0,0,0},{0,0,0},{0,0,0});
  scene::camera = new me::camera("camera", me::camera_type::PERSPECTIVE, 50, aspect, 0.1, 100, width, height, cam_transform);
  rendererApi->viewport(me::scene::camera, x, y, width, height);
  scene::setup();

  me::scene_packet* packet = me::fformat::read_mesh("/home/edvinskomputa/Dokument/OnePunchEngine/src/res/mega test of doom.dae");
  packet->register_all();
  me::mesh* mesh = packet->meshes["Cube_011-mesh"];

  me::transform transform1({128, 128, 0}, {0, 0, 0}, {256, 256, 0});
  me::transform transform2({564, 325, 0}, {0, 0, 0}, {256, 256, 0});
  me::ui::ui_button* button1 = new me::ui::ui_button("en knapp", transform1, mesh, new me::wcolor(me::wcolor_type::RGBA, new me::vec4f(0.4F, 0.8F, 0.2F, 1.0F)), button_press);
  me::ui::ui_button* button2 = new me::ui::ui_button("en knapp", transform2, mesh, new me::wcolor(me::wcolor_type::RGBA, new me::vec4f(0.9F, 0.2F, 0.2F, 1.0F)), button_press);
  scene::registerItem(button1);
  //scene::registerItem(button2);
}

void me::scene_2d_viewport::onRender()
{
  rendererApi->reset();
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
    scene::camera->transform.location.z+=posY*0.1F;
  }else if (action==ME_MOUSE_MOVE && isPressed(ME_MOUSE_MIDDLE_BUTTON))
  {
    scene::camera->transform.rotation.x+=posY*0.1F;
    scene::camera->transform.rotation.z+=posX*0.1F;
  }
  return scene::onMouseInput(action, posX, posY, button);
}
bool me::scene_2d_viewport::onKeyInput(int action, int key)
{
  return scene::onKeyInput(action, key);
}
