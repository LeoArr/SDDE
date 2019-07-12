#ifndef WALL
#define WALL

#include <GameTextManager.h>
#include <objects/MouseInteractable.h>
#include <SDLGameObject.h>
#include <InputHandler.h>
#include <iostream>

class Wall : public SDLGameObject, public MouseInteractable {
    public:
        Wall();
        void update();
        void draw(Camera *camera);
        void draw();
        void clear();
        void load(const GameObjectParams *params);

        void onClick() {
        }
        void onMouseOver() {
	  GameTextManager::instance()->addInfoText("2", "INTE \n permanent", _position.getX(), _position.getY());
        }
        bool isMouseOvered(Vector2D *mousePos);
    
};

#endif
