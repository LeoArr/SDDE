#ifndef PROP
#define PROP

#include <objects/MouseInteractable.h>
#include <SDLGameObject.h>
#include <InputHandler.h>
#include <iostream>

class Prop : public SDLGameObject {
    public:
        Prop();
        void update();
        void draw(Camera *camera);
        void draw();
        void clear();
        void load(const GameObjectParams *params);
    private:
        int _ticks;
};

#endif