#ifndef CAMERA
#define CAMERA

#include <utils/Vector2D.h>

class Camera {
    public:
        Camera() : _pos(), _targetPos(), _posStep(), _zoom(1), _targetZoom(1) {}
        Camera(Vector2D pos) : _pos(pos), _targetPos(), _posStep(), _zoom(1), _targetZoom(1) {}
        
        void setPos(Vector2D pos) {
            _pos = pos;
        }
        Vector2D getPos() {
            return _pos;
        }
        void setZoom(float zoom) {
            _zoom = zoom;
        }
        float getZoom() {
            return _zoom;
        }

        void update();

        void transitionTo(Vector2D targetPos, int steps);
        void transitionTo(Vector2D targetPos, float targetZoom, int steps);
        void transitionTo(float targetZoom, int steps);


        void relativeTransition(Vector2D relativePos, int steps);
        void relativeTransition(Vector2D relativePos, float relativeZoom, int steps);
        void relativeTransition(float relativeZoom, int steps);

        
    private:
        Vector2D _pos, _targetPos, _posStep;
        float _zoom, _targetZoom, _zoomStep;
        int _currentSteps, _targetSteps;

        void newTransition(int steps);
};

#endif