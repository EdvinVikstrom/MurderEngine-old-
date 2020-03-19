#include "workplace.h"

ui_workplace::ui_workplace(unsigned int width, unsigned int height, mVec3d camera)
{
  ui_workplace::width = width;
  ui_workplace::height = height;
  ui_workplace::camera = camera;
}

void ui_workplace::render()
{
  for (auto i : ui_workplace::items)
  {
    if (i->visible)
      i->render();
  }
}
void ui_workplace::loop()
{
  for (auto i : ui_workplace::items)
  {
    if (i->visible)
      i->loop();
  }
}

bool ui_workplace::mouseClicked(int button)
{
  for (auto i : ui_workplace::items)
  {
    if (i->visible && i->mouseClicked(*(info->cursorX), *(info->cursorY), button))
      return true;
  }
  return false;
}
bool ui_workplace::mousePressed(int button)
{
  for (auto i : ui_workplace::items)
  {
    if (i->visible && i->mousePressed(*(info->cursorX), *(info->cursorY), button))
      return true;
  }
  return false;
}
bool ui_workplace::mousePressing(int button, int ms)
{
  for (auto i : ui_workplace::items)
  {
    if (i->visible && i->mousePressing(*(info->cursorX), *(info->cursorY), button, ms))
      return true;
  }
  return false;
}
bool ui_workplace::mouseRelease(int button)
{
  for (auto i : ui_workplace::items)
  {
    if (i->visible && i->mouseRelease(*(info->cursorX), *(info->cursorY), button))
      return true;
  }
  return false;
}
void ui_workplace::mouseWheel(double offsetX, double offsetY)
{
  for (auto i : ui_workplace::items)
  {
    if (i->visible)
      i->mouseWheel(offsetX, offsetY);
  }
}
void ui_workplace::mouseMove(double offsetX, double offsetY)
{
  for (auto i : ui_workplace::items)
  {
    if (i->visible)
      i->mouseMove(offsetX, offsetY);
  }
}
bool ui_workplace::keyPressed(int key)
{
  for (auto i : ui_workplace::items)
  {
    if (i->visible && i->keyPressed(key))
      return true;
  }
  return false;
}
bool ui_workplace::keyRelease(int key)
{
  for (auto i : ui_workplace::items)
  {
    if (i->visible && i->keyRelease(key))
      return true;
  }
  return false;
}

state_info* ui_workplace::getStateInfo()
{
  return info;
}

void ui_workplace::setStateInfo(state_info* info)
{
  ui_workplace::info = info;
}
