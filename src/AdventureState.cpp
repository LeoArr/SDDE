#include <states/AdventureState.h>
#include <Logger.h>
#include <GameTextManager.h>

const std::string AdventureState::_stateId = "AdventureState";

AdventureState::~AdventureState() {
    Logger::instance()->log("Destroying Adventure state");
    onExit();
}

void AdventureState::render(SDL_Renderer *renderer) {
    for (auto layer : *(_gameObjectsLayers.getLayers())) {
      for (auto object : *(layer.second->getObjects())) {
	object->draw();
      }
    }
    GameTextManager::instance()->render();
    for (auto object : _hudObjects) {
	object->draw();
    }
}

bool exitCommandIsPressed() {
  return InputHandler::instance()->isKeyDown(SDL_SCANCODE_LCTRL) &&
    (InputHandler::instance()->isKeyPressed(SDL_SCANCODE_DELETE) ||
     InputHandler::instance()->isKeyPressed(SDL_SCANCODE_ESCAPE));
}

bool AdventureState::update(bool isTopState) {
    if (!isTopState)
        return true;
    if (exitCommandIsPressed())
        return false;

    for (auto layer : *(_gameObjectsLayers.getLayers())) {
      for (auto object : *(layer.second->getObjects())) {
	object->update();
      }
    }
    for (auto object : _hudObjects) {
	object->update();
    }
    GameTextManager::instance()->update();
    return true;
}

bool AdventureState::onEnter() {
    Logger::instance()->log("Adventure state entering");
    StateParser::instance()->parseState("test-state.xml", &_hudObjects, &_textureIds, &_gameState);
    StateParser::instance()->parseSceneObjects("test-scene.xml", &_gameObjectsLayers);
    Logger::instance()->log("Adventure state entering done");
    
    return true;
}

bool AdventureState::onExit() {
    Logger::instance()->log("Adventure state exiting");
    _gameObjectsLayers.clear();
    for (auto hudObj : _hudObjects) {
      delete hudObj;
    }
    _hudObjects.clear();
    _textureIds.clear();
    Logger::instance()->log("Adventure state exiting done");
    return true;
}

