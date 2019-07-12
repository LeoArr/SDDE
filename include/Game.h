#ifndef GAME
#define GAME

#include <GameStateMachine.h>
#include <ConfigParams.h>
#include <Logger.h>
#include <SDL2/SDL.h>
#include <utils/Vector2D.h>
#include <iostream>

enum ScreenMode {
  WINDOWED = 0,
  FULL = 2,
  FULL_DESKTOP = 1,
  number_of_elements = 3
};

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

	Uint32 getScreenMode(ScreenMode mode);
	void nextScreenMode();

	ScreenMode _screenMode;
        bool _isRunning;
        int _fps, _width, _height;
        Uint32 _delayTime;
        const char* _title;
};

#endif
