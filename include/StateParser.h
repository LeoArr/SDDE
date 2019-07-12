#ifndef STATE_PARSER
#define STATE_PARSER

#include <GameObjectFactory.h>
#include <GameObjectParams.h>
#include <objects/MouseInteractable.h>
#include <GameObjectsLayers.h>
#include <TextureManager.h>
#include <GameObject.h>
#include <ConfigParams.h>
#include <tinyxml.h>
#include <iostream>
#include <map>
#include <vector>
#include <map>

class StateParser {
    public: 
        static StateParser *instance() {
            if (_instance == 0) {
                _instance = new StateParser();
            }
            return _instance;
        }
        void parseConfig(ConfigParams *config);

        bool parseState(std::string stateFile,
            std::vector<GameObject*> *gameObjects = NULL,
            std::vector<std::string> *textureIds = NULL,
            std::map<std::string, std::string> *gameState = NULL);
        bool parseSceneObjects(std::string fileName, GameObjectsLayers *gameObjectsLayers);
    private:
        StateParser();
        bool parseObjects(TiXmlElement *stateRoot,
            std::vector<GameObject*> *gameObjects);

        bool parseTextures(TiXmlElement *stateRoot,
            std::vector<std::string> *textureIds);

        bool parseGameState(TiXmlElement *stateRoot,
            std::map<std::string, std::string> *gameState);

	bool parseFonts(TiXmlElement *stateRoot);

	void addClickBoxes(MouseInteractable *mi, TiXmlElement *elem);

        static StateParser *_instance;
};

#endif
