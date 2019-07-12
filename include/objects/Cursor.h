#ifndef CURSOR
#define CURSOR

#include <SDLGameObject.h>

class Cursor : public SDLGameObject {
    public:
        Cursor();
        void update();
        void draw(Camera *camera);
        void draw();
        void clear();
        void load(const GameObjectParams *params);
    
};

#endif