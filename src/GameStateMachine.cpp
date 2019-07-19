#include <GameStateMachine.h>
#include <Logger.h>

GameStateMachine::~GameStateMachine() {
    for (auto state : _gameStates) {
        delete state;
    }
    _gameStates.clear();
}

void GameStateMachine::pushState(GameState* newState) {
    _gameStates.push_back(newState);
    _gameStates.back()->onEnter();
}

void GameStateMachine::popState() {
    if (_gameStates.empty()) return;
    if (_gameStates.back()->onExit()) {
        delete _gameStates.back();
        _gameStates.pop_back();
    }
}

void GameStateMachine::changeState(GameState* newState) {
    if(_gameStates.empty()) {
        pushState(newState);
    } else {
        if (_gameStates.back()->getStateId() != newState->getStateId()) {
            popState();
        }
        pushState(newState);
    }
}

bool GameStateMachine::update() {
  if (_gameStates.empty())
    return false;
  bool isFirst = true;
  auto it = _gameStates.end();
  while (it > _gameStates.begin()) {
    it--;
    if (!(*it)->update(isFirst)) {
      Logger::instance()->log("NOOOOT");
      if ((*it)->onExit()) {
	delete (*it);
	it = _gameStates.erase(it);
      }
    }
    isFirst = false;
  }
  return true;
}

void GameStateMachine::render(SDL_Renderer *renderer) {
    std::for_each(_gameStates.begin(), _gameStates.end(), [renderer](GameState *state) {
        state->render(renderer);
    });
}
