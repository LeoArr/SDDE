#include <scripting/LogEventToken.h>
#include <scripting/ConditionalEqualityToken.h>
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

    ScriptToken* conToken = new ConditionalEqualityToken("fps", "30", true);
    ScriptToken* token = new LogEventToken("HEEEEEEEEEEEEEEEEEEEJ");
    conToken->addChild(token);
    conToken->run();
    delete token;
#endif

    _isRunning = true;
    Logger::instance()->log("Game init done");
    return true;
}

void Game::initWindowAndRenderer() {
  int flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | (getScreenMode(_screenMode)) |
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
    _screenMode = static_cast<ScreenMode>(ConfigParams::instance()->getI("screen-mode"));
    std::string sTitle = ConfigParams::instance()->get("title");
    _title = sTitle.c_str();
}

Uint32 Game::getScreenMode(ScreenMode mode) {
  switch (mode) {
  case ScreenMode::FULL:
    return SDL_WINDOW_FULLSCREEN;
  case ScreenMode::FULL_DESKTOP:
    return SDL_WINDOW_FULLSCREEN_DESKTOP;
  default:
    return 0;
  }
}

void Game::nextScreenMode() {
  _screenMode = static_cast<ScreenMode>((static_cast<int>(_screenMode) + 1) % static_cast<int>(ScreenMode::number_of_elements));
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
      nextScreenMode();
      ConfigParams::instance()->addParam("screen-mode", std::to_string(static_cast<int>(_screenMode)));
      
      SDL_SetWindowFullscreen(_window, getScreenMode(_screenMode));
      GameTextManager::instance()->addInfoText("screenModeChange", "Screen mode: " + std::to_string(static_cast<int>(_screenMode) + 1) + "/" + std::to_string(static_cast<int>(ScreenMode::number_of_elements)), 0, 0, 100);
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
