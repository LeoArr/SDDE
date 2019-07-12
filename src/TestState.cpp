#include <states/TestState.h>
#include <Logger.h>
#include <GameTextManager.h>

const std::string TestState::_stateId = "TestState";

TestState::~TestState() {
    Logger::instance()->log("Destroying test state");
    onExit();
}

void TestState::render(SDL_Renderer *renderer) {
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

bool TestState::update(bool isTopState) {
    if (!isTopState)
        return true;
    if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_DELETE))
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

bool TestState::onEnter() {
    Logger::instance()->log("Test state entering");
    StateParser::instance()->parseState("test-state.xml", &_hudObjects, &_textureIds, &_gameState);
    StateParser::instance()->parseSceneObjects("test-scene.xml", &_gameObjectsLayers);
    Logger::instance()->log("Test state entering done");
    
    return true;
}

bool TestState::onExit() {
    Logger::instance()->log("Test state exiting");
    _gameObjectsLayers.clear();
    _hudObjects.clear();
    _textureIds.clear();
    Logger::instance()->log("Test state exiting done");
    return true;
}

