#include <Camera.h>

void Camera::newTransition(int steps) {
    _targetSteps = steps;
    _currentSteps = 0;
    _posStep = (_targetPos - _pos) / steps;
    _zoomStep = (_targetZoom - _zoom) / steps;
}

void Camera::transitionTo(Vector2D targetPos, int steps) {
    _targetPos = targetPos;
    newTransition(steps);
}
void Camera::transitionTo(Vector2D targetPos, float targetZoom, int steps) {
    _targetPos = targetPos;
    _targetZoom = targetZoom;
    newTransition(steps);
}
void Camera::transitionTo(float targetZoom, int steps) {
    _targetZoom = targetZoom;
    newTransition(steps);
}

void Camera::relativeTransition(Vector2D relativePos, int steps) {
    _targetPos = _pos + relativePos;
    newTransition(steps);
}
void Camera::relativeTransition(Vector2D relativePos, float relativeZoom, int steps) {
    _targetPos = _pos + relativePos;
    _targetZoom = _zoom + relativeZoom;
    newTransition(steps);
}
void Camera::relativeTransition(float relativeZoom, int steps) {
    _targetZoom = _zoom + relativeZoom;
    newTransition(steps);
}

void Camera::update() {
    if (_currentSteps == _targetSteps) return;
    if (_pos != _targetPos) {
        _pos += _posStep;
    }
    if (_zoom != _targetZoom) {
        _zoom += _zoomStep;
    }
    _currentSteps++;
}