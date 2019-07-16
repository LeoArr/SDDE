#include <objects/Prop.h>
#include <Logger.h>

Prop::Prop() : SDLGameObject() {
    _ticks = 0;
}

void Prop::update() {
  _velocity = _velocity + (_acceleration / ConfigParams::instance()->getI("fps"));
  _position += _velocity;
  if (_numFrames < 2 || _animSpeed == 0) return;
  _curFrame = _baseFrame + (int)((_ticks / _animSpeed ) % (_numFrames));
  if (_ticks < _animSpeed * _numFrames) {
    _ticks++;
  } else {
    if (_loop) {
      _ticks++;
    }
  }
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
