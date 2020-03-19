#include "item.h"

item::item(double posX, double posY, double scaleX, double scaleY, bool visible, bool cameraAffected)
{
  item::posX = posX;
  item::posY = posY;
  item::scaleX = scaleX;
  item::scaleY = scaleY;
  item::visible = visible;
  item::cameraAffected = cameraAffected;
}

void item::loop() { }
void item::render() { }
bool item::mouseClicked(int cursorX, int cursorY, int button) { }
bool item::mousePressed(int cursorX, int cursorY, int button) { }
bool item::mousePressing(int cursorX, int cursorY, int button, int ms) { }
bool item::mouseRelease(int cursorX, int cursorY, int button) { }
void item::mouseWheel(double offsetX, double offsetY) { }
void item::mouseMove(double offsetX, double offsetY) { }
bool item::keyPressed(int key) { }
bool item::keyRelease(int key) { }
