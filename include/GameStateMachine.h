#ifndef GAME_STATE_MACHINE
#define GAME_STATE_MACHINE

#include "./states/GameState.h"
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <algorithm>

class GameStateMachine {
    public:
        ~GameStateMachine();
        void pushState(GameState *newState);
        void popState();
        void changeState(GameState *newState);

        void update();
        void render(SDL_Renderer *renderer);
    
    private:
        std::vector<GameState*> _gameStates;
};

#endif
