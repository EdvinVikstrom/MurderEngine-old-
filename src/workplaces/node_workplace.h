#ifndef NODE_WORKPLACE_H
  #define NODE_WORKPLACE_H

#include <vector>
#include "workplace.h"
#include "../MurderEngineMath.h"
#include "../nodes/node.h"

class node_workplace : public ui_workplace {

private:

  std::vector<node*> nodes;
  std::vector<item*> inHand;
  node_socket* wireInHand;

public:

  node_workplace(unsigned int width, unsigned int height, mVec3d camera);

  node_socket* getSocketAt(double cursorX, double cursorY);

  void addNode(node_info info, double posX, double posY);

  void render() override;

  void loop() override;

  bool mouseClicked(int button) override;
  bool mousePressed(int button) override;
  bool mousePressing(int button, int ms) override;
  bool mouseRelease(int button) override;
  void mouseWheel(double offsetX, double offsetY) override;
  void mouseMove(double offsetX, double offsetY) override;
  bool keyPressed(int key) override;
  bool keyRelease(int key) override;

};

#endif
