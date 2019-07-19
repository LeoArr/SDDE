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
  MouseInteractable::update(&_position);
}

void Wall::draw(Camera *camera) {
    SDLGameObject::draw();
    drawBoxes();
}
void Wall::draw() {
    SDLGameObject::draw();
    drawBoxes();
}
