#include <iostream>
#include "../ui/item.h"
#include "node.h"
#include "../renderer/render_helper.h"
#include "../utilities/Utilities.h"
#include "node_render.h"

node::node(double posX, double posY, double scaleX, double scaleY, bool visible, bool cameraAffected, node_info info) : item(posX, posY, scaleX, scaleY, visible, cameraAffected)
{
  node::info = info;
  for (node_socket* socket : node::info.sockets)
    socket->setParent(this);
}

void node::render()
{
  int panelColor = node::info.category;
  render_rectangle(NODE_BACKGROUND_COLOR, node::posX, node::posY, node::scaleX, node::scaleY, true);
  render_rectangle(panelColor, node::posX, node::posY, node::scaleX, NODE_PANEL_HEIGHT, true);
  //render_rectangle(0xFF000000, node::posX, node::posY, node::scaleX, node::scaleY, false);
  node_render_update_socket_pos(this);
  node_render_sockets(this);
}

void node::loop()
{
}
bool node::mouseClicked(int cursorX, int cursorY, int button)
{
  return false;
}
bool node::mousePressed(int cursorX, int cursorY, int button)
{
  return false;
}
bool node::mousePressing(int cursorX, int cursorY, int button, int ms)
{
  return false;
}
bool node::mouseRelease(int cursorX, int cursorY, int button)
{
  return false;
}
void node::mouseWheel(double offsetX, double offsetY)
{

}
void node::mouseMove(double offsetX, double offsetY)
{

}
bool node::keyPressed(int key)
{
  return false;
}
bool node::keyRelease(int key)
{
  return false;
}
