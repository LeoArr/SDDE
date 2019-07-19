#ifndef PROP
#define PROP

#include <objects/MouseInteractable.h>
#include <objects/EventTriggerer.h>
#include <SDLGameObject.h>
#include <GameTextManager.h>
#include <InputHandler.h>
#include <iostream>

class Prop : public SDLGameObject, public MouseInteractable, public EventTriggerer {
    public:
        Prop();
        void update();
        void draw(Camera *camera);
        void draw();
        void clear();
        void load(const GameObjectParams *params);

	void onClick() {
	  EventTriggerer::onClick();
	}

        void onMouseOver() {
	  GameTextManager::instance()->addInfoText("2", "INTE \n permanent", _position.getX(), _position.getY());
        }
	
    private:
        int _ticks;
};

#endif
