#include <SDLGameObject.h>
#include <TextureManager.h>

SDLGameObject::SDLGameObject() {
}

void SDLGameObject::load(const GameObjectParams *params) {
    _position = Vector2D(params->getI("x"), params->getI("y"));
    _velocity = Vector2D(0,0);
    _acceleration = Vector2D(0,0);
    _width = params->getI("width");
    _height = params->getI("height");
    _textureId = params->get("textureId");
    _baseRow = params->getI("baseRow");
    _baseFrame = params->getI("baseFrame");
    _numFrames = params->getI("numFrames");
    _animSpeed = params->getI("animSpeed");
    delete params;
    _curFrame = _baseFrame;
    _curRow = _baseRow;
}

void SDLGameObject::draw(Camera *camera) {
    Vector2D relPos = ((_position - camera->getPos()) * camera->getZoom()) + (Game::instance()->getWindowSize() / 2);
    TextureManager::instance()->drawFrame(_textureId, (int)relPos.getX(), (int)relPos.getY(),
        _width, _height, _curRow, _curFrame, camera->getZoom(), Game::instance()->getRenderer());
}
void SDLGameObject::draw() {
    TextureManager::instance()->draw(_textureId, (int)_position.getX(), (int)_position.getY(),
        _width, _height, _curRow, _curFrame, 1, Game::instance()->getRenderer());
}