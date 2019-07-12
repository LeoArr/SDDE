#include <objects/Cursor.h>
#include <InputHandler.h>

Cursor::Cursor() : SDLGameObject() { }

void Cursor::load(const GameObjectParams *params) {
    SDLGameObject::load(params);
}

void Cursor::update() {
    _position = (*InputHandler::instance()->getMousePosition());
    if (InputHandler::instance()->getMouseButtonState(MouseButton::LEFT)) {
        _curFrame = 1;
    } else {
        _curFrame = 0;
    }
}

void Cursor::draw(Camera *camera) {
    draw();
}

void Cursor::draw() {
    SDLGameObject::draw();
}