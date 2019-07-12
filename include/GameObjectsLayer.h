#ifndef GAME_OBJECTS_LAYER
#define GAME_OBJECTS_LAYER

#include <GameObject.h>
#include <vector>
#include <algorithm>

class GameObjectsLayer {
public:
  GameObjectsLayer() : _isDirty(false) {};
  ~GameObjectsLayer() {
    for (auto it : _gameObjects) {
      delete it;
    }
    _gameObjects.clear();
  }
  
  void add(GameObject *gameObject) {
    _gameObjects.push_back(gameObject);
    _isDirty = true;
  }

  bool remove(GameObject *gameObject) {
    auto vecObj = std::find(_gameObjects.begin(), _gameObjects.end(), gameObject);
    if (vecObj != _gameObjects.end()) {
      _gameObjects.erase(vecObj);
      delete (*vecObj);
      _isDirty = true;
      return true;
    }
    return false;
  }

  std::vector<GameObject*>* getObjects() {
    return &_gameObjects;
  }
  
  bool isDirty() {
    return _isDirty;
  }

  void wasTouched() {
    _isDirty = false;
  }

private:
  bool _isDirty;
  std::vector<GameObject*> _gameObjects;
};

#endif
