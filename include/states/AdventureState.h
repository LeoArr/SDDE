#ifndef ADVENTURE_STATE
#define ADVENTURE_STATE

#include <StateParser.h>
#include <GameObject.h>
#include <GameObjectsLayers.h>
#include <GameObjectParams.h>
#include <states/GameState.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

class AdventureState: public GameState {
    public:
        ~AdventureState();
        bool update(bool isTopState = false);
        void render(SDL_Renderer *renderer);
        
        bool onEnter();
        bool onExit();
        std::string getStateId() const {
            return _stateId;
        }
    private:
        GameObjectsLayers _gameObjectsLayers;
        std::vector<GameObject*> _hudObjects;
        std::vector<std::string> _textureIds;
        GameObjectParams _gameState;
        static const std::string _stateId;
};

#endif
