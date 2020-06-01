#include "scene_2d_viewport.h"
#include "../../loader/scene_format.h"
#include "../../loader/image_format.h"
#include "../../loader/file_format.h"
#include "../../audio/audio_system.h"

#include <iostream> // remove

void me::scene_2d_viewport::onPreInit(MeInstance* instance) { }
void me::scene_2d_viewport::onDestroyed(MeInstance* instance) { }

void button_callback(MeInputEventContext* context)
{
  std::cout << "button preäsed!\n";
}

void me::scene_2d_viewport::onInit(MeInstance* instance)
{
  float aspect = (float)width/(float)height;
  me::vec3 position(0, 0, 0);
  me::vec3 rotation(0.0F, 0.0F, 0.0F);
  scene::camera = new me::Camera("camera", me::CameraProjection::PROJ_VIEW_2D, me::maths::to_radians(50.0F), aspect, -1.0F, 1.0F, width, height, position, rotation);
  scene::onInit(instance);

  me::Image* image = new me::Image;
  me::format::loadImage(instance, "src/res/untitled.bmp", image, FLAG_METADATA_ALL);

  ui->elements["test"] = new me::ui::button(instance, new me::wcolor(image), 0, 0, 24, 24, button_callback);

  /* setting up renderer */
  instance->renderer->setupMeshRenderer(instance);
  instance->renderer->setupImageRenderer(instance);
}

void me::scene_2d_viewport::onRender(MeRenderer* renderer)
{
  scene::onRender(renderer);
  ui->render(renderer);
}
void me::scene_2d_viewport::onLoop(MeInstance* instance)
{
  scene::onLoop(instance);
  ui->update(instance);
}

bool me::scene_2d_viewport::onMouseInput(MeInputEventContext* context, int action, double posX, double posY, int button)
{
  if (ui->mouseEvent(context, action, posX, posY, button))
    return true;
  return scene::onMouseInput(context, action, posX, posY, button);
}
bool me::scene_2d_viewport::onKeyInput(MeInputEventContext* context, int action, int key)
{
  if (ui->keyboardEvent(context, action, key))
    return true;
  return scene::onKeyInput(context, action, key);
}
