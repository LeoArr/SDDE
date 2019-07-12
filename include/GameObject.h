#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <GameObjectParams.h>
#include <Camera.h>

class GameObject {
    public:
        virtual ~GameObject() {}
        virtual void update() = 0;
        virtual void draw(Camera *camera) = 0;
        virtual void draw() = 0;

        virtual void load(const GameObjectParams *params) = 0;

    protected:
        GameObject() {}
};

#endif