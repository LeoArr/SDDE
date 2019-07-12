#ifndef GAME_OBJECTS_LAYERS
#define GAME_OBJECTS_LAYERS

#include <Logger.h>
#include <GameObjectsLayer.h>
#include <map>

class GameObjectsLayers {
public:
  GameObjectsLayers() : _isDirty(false) {};
  ~GameObjectsLayers() {
    clear();
  }

  void clear() {
    for (auto layer : _layers) {
      delete layer.second;
    }
    _layers.clear();
  }

  GameObjectsLayer* newLayer(int z) {
    if (z < 0) return NULL;
    auto layer = _layers.find(z);
    if (layer != _layers.end()) {
      _layers.erase(layer);
    }
    _isDirty = true;
    _layers[z] = new GameObjectsLayer();
    return _layers[z];
  }

  void addObject(int z, GameObject* object) {
    if (z < 0) return;
    if (_layers.find(z) == _layers.end()) {
      newLayer(z);
    }
    _layers[z]->add(object);
  }

  bool removeObject(GameObject* object, int z = -1) {
    if (z < 0) {
      for (auto layer : _layers) {
	if (layer.second->remove(object)) {
	  return true;
	}
      }
      return false;
    }
    if (_layers.find(z) != _layers.end()) {
      _layers[z]->remove(object);
      return true;
    }
    return false;
  }

  std::vector<GameObject*>* getObjects(int z) {
    if (_layers.find(z) != _layers.end()) {
      return _layers[z]->getObjects();
    }
    return NULL;
  }

  std::map<int, GameObjectsLayer*>* getLayers() {
    return &_layers;
  }

private:
  std::map<int, GameObjectsLayer*> _layers;
  bool _isDirty;
};

#endif
