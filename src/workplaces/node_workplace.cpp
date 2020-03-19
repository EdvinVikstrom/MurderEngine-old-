#include <iostream>
#include "node_workplace.h"
#include "../nodes/node.h"
#include "../nodes/category/converter/math_node.h"
#include "../nodes/node_render.h"
#include "../utilities/FileUtils.h"

static void connectSockets(node_socket* socket1, node_socket* socket2)
{
  socket1->connections.push_back(socket2);
  ((node*)socket1->parent)->info.onUpdate();
}

node_workplace::node_workplace(unsigned int width, unsigned int height, mVec3d camera) : ui_workplace(width, height, camera)
{
  unsigned int bufferSize = 8;
  char* buffer = new char[bufferSize];
  file_utils_read("/home/edvinskomputa/Dokument/Hejsan.txt", bufferSize, buffer);
  std::cout << buffer << "\n";
}

node_socket* node_workplace::getSocketAt(double cursorX, double cursorY)
{
  for (node* _node : node_workplace::nodes)
  {
    for (node_socket* socket : _node->info.sockets)
    {
      double posX = socket->posX;
      double posY = socket->posY;
      if (cursorX >= posX && cursorX <= posX + NODE_SOCKET_SIZE && cursorY >= posY && cursorY <= posY + NODE_SOCKET_SIZE)
        return socket;
    }
  }
  return nullptr;
}

void node_workplace::addNode(node_info info, double posX, double posY)
{
  node* _node = new node(posX, posY, info.default_scale.x, info.default_scale.y, true, true, info);
  node_workplace::nodes.push_back(_node);
  this->items.push_back(_node);
}

void node_workplace::render()
{
  ui_workplace::render();
  if (node_workplace::wireInHand != nullptr)
    node_render_socket_wire(node_workplace::wireInHand->posX+(NODE_SOCKET_SIZE/2), node_workplace::wireInHand->posY+(NODE_SOCKET_SIZE/2), *(info->cursorX), *(info->cursorY));
}

void node_workplace::loop()
{
  ui_workplace::loop();
}

bool node_workplace::mouseClicked(int button)
{
  if (ui_workplace::mouseClicked(button))
    return true;
  return false;
}

bool node_workplace::mousePressed(int button)
{
  if (ui_workplace::mousePressed(button))
    return true;
  for (auto i : this->items)
  {
    if ((*info->cursorX) >= i->posX && (*info->cursorX) <= i->posX + i->scaleX && (*info->cursorY) >= i->posY && (*info->cursorY) <= i->posY + NODE_PANEL_HEIGHT)
    {
      node_workplace::inHand.push_back(i);
      return true;
    }
  }
  node_workplace::wireInHand = getSocketAt((*info->cursorX), (*info->cursorY));
  return false;
}
bool node_workplace::mousePressing(int button, int ms)
{
  if (ui_workplace::mousePressing(button, ms))
    return true;
  return false;
}
bool node_workplace::mouseRelease(int button)
{
  node_workplace::inHand.clear();
  node_socket* target = getSocketAt((*info->cursorX), (*info->cursorY));
  if (target != nullptr && target != node_workplace::wireInHand && target->dir != node_workplace::wireInHand->dir)
  {
    if (target->dir==NODE_SOCKET_IN)
      connectSockets(node_workplace::wireInHand, target);
    else
      connectSockets(target, node_workplace::wireInHand);
  }
  node_workplace::wireInHand = nullptr;
  if (ui_workplace::mouseRelease(button))
    return true;
  return false;
}
void node_workplace::mouseWheel(double offsetX, double offsetY)
{
  ui_workplace::mouseWheel(offsetX, offsetY);
}
void node_workplace::mouseMove(double offsetX, double offsetY)
{
  ui_workplace::mouseMove(offsetX, offsetY);
  for (auto i : node_workplace::inHand)
  {
    i->posX+=offsetX;
    i->posY+=offsetY;
  }
}
bool node_workplace::keyPressed(int key)
{
  if (ui_workplace::keyPressed(key))
    return true;
  if (key==65)
    node_workplace::addNode(math_node_create_info(), (*info->cursorX), (*info->cursorY));
  return false;
}
bool node_workplace::keyRelease(int key)
{
  if (ui_workplace::keyRelease(key))
    return true;
  return false;
}
