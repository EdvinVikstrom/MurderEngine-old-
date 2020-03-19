#ifndef ITEM_H
  #define ITEM_H

class item {

public:

  double posX, posY;
  double scaleX, scaleY;
  bool visible;
  bool cameraAffected;

  item(double posX, double posY, double scaleX, double scaleY, bool visible, bool cameraAffected);

  virtual void loop();
  virtual void render();
  virtual bool mouseClicked(int cursorX, int cursorY, int button);
  virtual bool mousePressed(int cursorX, int cursorY, int button);
  virtual bool mousePressing(int cursorX, int cursorY, int button, int ms);
  virtual bool mouseRelease(int cursorX, int cursorY, int button);
  virtual void mouseWheel(double offsetX, double offsetY);
  virtual void mouseMove(double offsetX, double offsetY);
  virtual bool keyPressed(int key);
  virtual bool keyRelease(int key);

};

#endif
