#include <objects/Prop.h>
#include <Logger.h>

Prop::Prop() : SDLGameObject() {
    _ticks = 0;
}

void Prop::update() {
    if (_numFrames < 2 || _animSpeed == 0) return;
    _curFrame = _baseFrame + (int)((_ticks / _animSpeed ) % (_numFrames));
    _ticks++;
    if (_ticks > _animSpeed * _numFrames)
        _ticks = 0;
}

void Prop::load(const GameObjectParams *params) {
    SDLGameObject::load(params);
}

void Prop::draw(Camera *camera) {
    SDLGameObject::draw();
}
void Prop::draw() {
    SDLGameObject::draw();
}