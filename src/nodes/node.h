#ifndef NODE_H
  #define NODE_H

#include <vector>
#include "../engine/MurderEngineCommon.h"
#include "../ui/item.h"

#define NODE_SOCKET_IN                    0x1
#define NODE_SOCKET_OUT                   0x2

#define NODE_SOCKET_SIZE                  0x12
#define NODE_SOCKET_WIRE_WIDTH            1.570796327F

#define NODE_SOCKET_DATA_TYPE_INT         0xFF2A2A2A
#define NODE_SOCKET_DATA_TYPE_FLOAT       0xFF3A3A4A
#define NODE_SOCKET_DATA_TYPE_STRING      0x5
#define NODE_SOCKET_DATA_TYPE_ARGB        0x6
#define NODE_SOCKET_DATA_TYPE_VECTOR      0x7
#define NODE_SOCKET_DATA_TYPE_WAVE        0x8

#define NODE_CATEGORY_INPUT               0xFF8F0000
#define NODE_CATEGORY_OUTPUT              0xFF8F8A00
#define NODE_CATEGORY_CONVERTER           0xFF1CB0DD
#define NODE_CATEGORY_LOGIC               0xFF00008F

#define NODE_PANEL_HEIGHT                 24
#define NODE_BACKGROUND_COLOR             0x8F1F2021

#include "node_socket.h"

struct node_info {

typedef void (*node_on_update_function)(node_info*);

  const char* name;
  unsigned int category;
  me::vec2d default_scale;
  std::vector<node_socket*> sockets;
  node_on_update_function updateFunction;

  void onUpdate()
  {
    (*updateFunction)(this);
    for (node_socket* socket : sockets)
    {
      for (node_socket* connection : socket->connections)
      {
        connection->value = socket->value;
        connection->valueLength = socket->valueLength;
      }
    }
  }

};

class node : public item {

public:

  node_info info;

  node(double posX, double posY, double scaleX, double scaleY, bool visible, bool cameraAffected, node_info info);

  void render() override;
  void loop() override;
  bool mouseClicked(int cursorX, int cursorY, int button) override;
  bool mousePressed(int cursorX, int cursorY, int button) override;
  bool mousePressing(int cursorX, int cursorY, int button, int ms) override;
  bool mouseRelease(int cursorX, int cursorY, int button) override;
  void mouseWheel(double offsetX, double offsetY) override;
  void mouseMove(double offsetX, double offsetY) override;
  bool keyPressed(int key) override;
  bool keyRelease(int key) override;
};

#endif
