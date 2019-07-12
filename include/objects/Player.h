#ifndef PLAYER
#define PLAYER

#include <SDLGameObject.h>
#include <InputHandler.h>


class Player : public SDLGameObject {
    public:
        Player();
        void update();
        void draw(Camera *camera);
        void draw();
        void clear();
        void load(const GameObjectParams *params);
    
};

#endif