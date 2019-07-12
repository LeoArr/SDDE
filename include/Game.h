#ifndef GAME
#define GAME

#include <GameStateMachine.h>
#include <ConfigParams.h>
#include <Logger.h>
#include <SDL2/SDL.h>
#include <utils/Vector2D.h>
#include <iostream>

class Game {
    public:
        static Game* instance() {
            if (_instance == 0) {
                _instance = new Game();
            }
            return _instance;
        }
        ~Game();
        void clear();
        bool init();
        void tick();
        bool isRunning() { return _isRunning; }

        SDL_Renderer* getRenderer() { return _renderer; }
        Vector2D getWindowSize();

    private:
        Game();
        static Game* _instance;

        SDL_Window* _window;
        SDL_Renderer* _renderer;
        GameStateMachine* _gameStateMachine;
        void handleEvents();
        void update();
        void render();

        void initVars();
        void initWindowAndRenderer();
        bool doResetGame();
        bool toggleFullscreen();

        bool _isRunning, _isFullscreen;
        int _fps, _width, _height;
        Uint32 _delayTime;
        const char* _title;
};

#endif