#ifndef GAME_STATE
#define GAME_STATE

#include <TextureManager.h>
#include <SDL2/SDL.h>
#include <string>

class GameState {
    public:
        virtual ~GameState() = default;
        virtual bool update(bool isTopState = false) = 0;
        virtual void render(SDL_Renderer * renderer) = 0;

        virtual bool onEnter() = 0;
        virtual bool onExit() = 0;

        virtual std::string getStateId() const = 0;
};

#endif
