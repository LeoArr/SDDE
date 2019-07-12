#include <objects/Player.h>

Player::Player() : SDLGameObject() { }

void Player::load(const GameObjectParams *params) {
    SDLGameObject::load(params);
    _curRow = 1;
}

void Player::update() {
    _velocity = Vector2D(0, 0);
    if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_RIGHT))
        _velocity += Vector2D(1, 0);
    if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_LEFT))
        _velocity += Vector2D(-1, 0);
    if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_UP))
        _velocity += Vector2D(0, -1);
    if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_DOWN))
        _velocity += Vector2D(0, 1);
    _velocity.normalize();
    _position += _velocity * 3;
    _curFrame = abs(int((((int)_position.getX() / 20) % 4)));
}

void Player::draw(Camera *camera) {
    SDLGameObject::draw(camera);
}

void Player::draw() {
    SDLGameObject::draw();
}