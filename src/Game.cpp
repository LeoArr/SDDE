#include <states/TestState.h>
#include <Game.h>
#include <Ticker.h>
#include <InputHandler.h>
#include <cstring>

Game* Game::_instance = 0;

Game::Game() {
    Logger::instance()->log("Game created");
}

Game::~Game() {
    clear();
}

void Game::clear() {
    Logger::instance()->log("Game clearing...");
    _isRunning = false;
    delete _gameStateMachine;
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    Logger::instance()->log("Game clearing done.");
}

bool Game::init() {
    Logger::instance()->log("Game init");
    initVars();
    initWindowAndRenderer();
    Logger::instance()->log("Game init: Setting vars done");
#ifdef DEBUG
    _gameStateMachine = new GameStateMachine();
    TestState *testState = new TestState();
    _gameStateMachine->pushState(testState);
#endif

    _isRunning = true;
    Logger::instance()->log("Game init done");
    return true;
}

void Game::initWindowAndRenderer() {
  int flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL |
    (_isFullscreen ? SDL_WINDOW_FULLSCREEN : 0) |
    SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_MOUSE_FOCUS |
    SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_INPUT_GRABBED;
  _window = SDL_CreateWindow(_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, flags);
    SDL_SetWindowBordered(_window, SDL_FALSE);
    _renderer = SDL_CreateRenderer(_window, -1, 0);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderSetLogicalSize(_renderer, _width, _height);
    
    SDL_RenderSetIntegerScale(_renderer, SDL_TRUE);
    SDL_Rect rec;
    rec.x = 0;
    rec.y = 0;
    rec.w = 960;
    rec.h = 540;
    SDL_RenderSetViewport(_renderer, &rec);
    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, ConfigParams::instance()->get("AA").c_str());
}

void Game::initVars() {
    _width = ConfigParams::instance()->getI("window-width");
    _height = ConfigParams::instance()->getI("window-height");
    _fps = ConfigParams::instance()->getI("fps");
    _delayTime = 1000.0f / _fps;
    _isFullscreen = ConfigParams::instance()->get("window-fullscreen") == "true";
    std::string sTitle = ConfigParams::instance()->get("title");
    _title = sTitle.c_str();
}

void Game::handleEvents() {
#ifdef DEBUG
    if (doResetGame()) return;
#endif
    if (!InputHandler::instance()->update())
        _isRunning = false;
    if (toggleFullscreen()) return;    
}

void Game::update() {
    _gameStateMachine->update();
}

void Game::render() {
    SDL_RenderClear(_renderer);
    _gameStateMachine->render(_renderer);
    SDL_RenderPresent(_renderer);
}

bool Game::doResetGame() {
    if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_LCTRL)
        && InputHandler::instance()->isKeyPressed(SDL_SCANCODE_R)) {
        StateParser::instance()->parseConfig(ConfigParams::instance());
        Game::instance()->clear();
        Game::instance()->init();
        return true;
    }
    return false;
}

bool Game::toggleFullscreen() {
    if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_LCTRL) && InputHandler::instance()->isKeyPressed(SDL_SCANCODE_F)) {
        _isFullscreen = !_isFullscreen;
        ConfigParams::instance()->addParam("window-fullscreen", _isFullscreen ? "true" : "false");
	const char* platform = SDL_GetPlatform();
	const char* windows = "Windows";
	Uint32 flag = platform == windows ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_FULLSCREEN_DESKTOP;
        SDL_SetWindowFullscreen(_window, _isFullscreen ? flag : 0);
        return true;
    }
    return false;
}

void Game::tick() {
    Uint32 ticks = SDL_GetTicks();

    handleEvents();
    update();
    render();

    Uint32 frameTime = SDL_GetTicks() - ticks;
    if (frameTime < _delayTime) {
        SDL_Delay((int) _delayTime - frameTime);
    }
    Ticker::instance()->increment();
}

Vector2D Game::getWindowSize() {
    return Vector2D(_width, _height);
}