#ifndef SDL_GAME_OBJECT
#define SDL_GAME_OBJECT

#include <GameObject.h>
#include <Game.h>
#include <utils/Vector2D.h>

class SDLGameObject : public GameObject {
    public:

        virtual void draw(Camera *camera);
        virtual void draw();
        virtual void update() = 0;
        virtual void load(const GameObjectParams *params);
        virtual Vector2D getCenterPos() {
            return _position + Vector2D(_width/2, _height/2);
        }


    protected:
        SDLGameObject();
        Vector2D _position, _velocity, _acceleration;
        int _width, _height, _curRow, _baseRow, _curFrame, _baseFrame, _numFrames, _animSpeed;
        std::string _textureId;
};

#endif