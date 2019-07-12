#include <objects/Wall.h>
#include <iostream>

Wall::Wall() : SDLGameObject() {
}

void Wall::load(const GameObjectParams *params) {
    SDLGameObject::load(params);
}

void Wall::update() {
  _position += Vector2D(0.1f, 0);
  if (isMouseOvered(InputHandler::instance()->getMousePosition())) {
    onMouseOver();
  }
}

bool Wall::isMouseOvered(Vector2D *mousePos) {
  return isMouseOveredInternal(&_position, mousePos);
}

void Wall::draw(Camera *camera) {
    SDLGameObject::draw();
    drawBoxes(&_position);
}
void Wall::draw() {
    SDLGameObject::draw();
    drawBoxes(&_position);
}