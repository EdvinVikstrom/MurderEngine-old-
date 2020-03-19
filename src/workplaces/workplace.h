#ifndef WORKPLACE_H
  #define WORKPLACE_H

class ui_workplace;

#include <vector>
#include "../ui/item.h"
#include "../MurderEngineMath.h"

class ui_workplace {

private:

  unsigned int width;
  unsigned int height;
  mVec3d camera;

protected:

  state_info* info;
  std::vector<item*> items;

public:

  /* camera: { x: posX, y: posY, z: zoom } */
  ui_workplace(unsigned int width, unsigned int height, mVec3d camera);

  virtual void render();
  virtual void loop();

  virtual bool mouseClicked(int button);
  virtual bool mousePressed(int button);

  /* Get calls every tick while mouse is pressed */
  virtual bool mousePressing(int button, int ms);
  virtual bool mouseRelease(int button);
  virtual void mouseWheel(double offsetX, double offsetY);
  virtual void mouseMove(double offsetX, double offsetY);
  virtual bool keyPressed(int key);
  virtual bool keyRelease(int key);

  virtual state_info* getStateInfo();
  virtual void setStateInfo(state_info* info);

};

#endif
