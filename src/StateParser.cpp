#include <StateParser.h>
#include <Logger.h>
#include <TextManager.h>

StateParser* StateParser::_instance = 0;

StateParser::StateParser() {
    Logger::instance()->log("State parser instantiated");
}

bool StateParser::parseState(std::string stateFile,
                            std::vector<GameObject*> *gameObjects,
                            std::vector<std::string> *textureIds,
                            GameObjectParams *gameState) {
    TiXmlDocument xmlDoc;
    if (!xmlDoc.LoadFile(ConfigParams::instance()->get("assets-folder") + 
                        ConfigParams::instance()->get("states-folder") + stateFile)) {
        std::cerr << xmlDoc.ErrorDesc() << std::endl;
        return false;
    }
    TiXmlElement *root = xmlDoc.RootElement();
    TiXmlElement* gameRoot = 0, *texturesRoot = 0, *objectsRoot = 0, *fontsRoot;
    for (auto e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (std::string(e->Value()) == "game") {
            gameRoot = e;
        } else if (std::string(e->Value()) == "textures") {
            texturesRoot = e;
        } else if (std::string(e->Value()) == "objects") {
            objectsRoot = e;
        } else if (std::string(e->Value()) == "fonts") {
	  fontsRoot = e;
	}
    }
    return  parseObjects(objectsRoot, gameObjects) &&
            parseTextures(texturesRoot, textureIds) &&
            parseGameState(gameRoot, gameState) &&
            parseFonts(fontsRoot);
}

bool StateParser::parseFonts(TiXmlElement *root) {
  for (auto elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
    std::string fileName = elem->Attribute("fileName");
    std::string id = elem->Attribute("id");
    std::string ptSize = elem->Attribute("ptSize");
    if (ptSize == "")
      TextManager::instance()->load(id, fileName);
    else
      TextManager::instance()->load(id, fileName, std::stoi(ptSize));
    Logger::instance()->log(id + " font added");
  }
  return true;
}

bool StateParser::parseSceneObjects(std::string fileName, GameObjectsLayers *gameObjectsLayers) {
  TiXmlDocument xmlDoc;
  if (!xmlDoc.LoadFile(ConfigParams::instance()->get("assets-folder") + 
                        ConfigParams::instance()->get("scenes-folder") + fileName)) {
    std::cerr << xmlDoc.ErrorDesc() << std::endl;
    return false;
  }
  TiXmlElement *root = xmlDoc.RootElement();
  for (auto elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
    addGameObject(elem, gameObjectsLayers);
  }
  return true;
}

void StateParser::addGameObject(TiXmlElement *elem, GameObjectsLayers *gameObjectsLayers) {
  GameObjectParams *params = new GameObjectParams();
  for (auto attr = elem->FirstAttribute(); attr != NULL; attr = attr->Next()) {
    std::string key = attr->Name();
    std::string value = attr->Value();
    params->addParam(key, value);
  }
  Logger::instance()->log("Creating:");
  Logger::instance()->log(elem->Attribute("type"));
  GameObject* gameObject = GameObjectFactory::instance()->create(elem->Attribute("type"));
  for (auto childElem = elem->FirstChildElement(); childElem != NULL; childElem = childElem->NextSiblingElement()) {
    if (std::string(childElem->Value()) == "boxes") {
      if (MouseInteractable *mi = dynamic_cast<MouseInteractable*>(gameObject)) {
	addClickBoxes(mi, childElem);
      }
    } else if (std::string(childElem->Value()) == "scripts") {
      if (EventTriggerer *et = dynamic_cast<EventTriggerer*>(gameObject)) {
      	addEventScripts(et, childElem);
      }
    }
  }
  Logger::instance()->log("Adding to layer: ");
  Logger::instance()->log(params->getI("z"));
  gameObjectsLayers->addObject(params->getI("z"), gameObject);
  gameObject->load(params);
  delete params;
}

void StateParser::addClickBoxes(MouseInteractable *mi, TiXmlElement *elem) {
    for (auto boxElem = elem->FirstChildElement(); boxElem != NULL; boxElem = boxElem->NextSiblingElement()) {
        if (std::string(boxElem->Value()) != "box") continue;
        int x {}, y {}, w {}, h {};
        for (auto attr = boxElem->FirstAttribute(); attr != NULL; attr = attr->Next()) {
            std::string key = attr->Name();
            if (key == "x")
                x = std::stoi(attr->Value());
            else if (key == "y")
                y = std::stoi(attr->Value());
            else if (key == "w")
                w = std::stoi(attr->Value());
            else if (key == "h")
                h = std::stoi(attr->Value());
            
        }
        mi->addClickBox(new ClickBox(new Vector2D(x, y), w, h));
    }
}

ScriptToken* buildScriptFromBody(TiXmlElement *elem) {
  ScriptToken* result = NULL;
  for (auto scriptElem = elem->FirstChildElement(); scriptElem != NULL; scriptElem = scriptElem->NextSiblingElement()) {
    std::string type = scriptElem->Attribute("type");
    if (type == "conditional-equality") {
      std::string key = scriptElem->Attribute("key");
      std::string value = scriptElem->Attribute("value");
      std::string equalsString = scriptElem->Attribute("equals");
      bool equals = equalsString != "false";
      result = new ConditionalEqualityToken(key, value, equals);
    } else if (type == "log-event") {
      std::string text = scriptElem->Attribute("text");
      result = new LogEventToken(text);
    }
    if (result != NULL) {
      Logger::instance()->log("Script added: " + type);
      result->addChild(buildScriptFromBody(scriptElem));
    }
  }
  return result;
}

void StateParser::addEventScripts(EventTriggerer *et, TiXmlElement *elem) {
  for (auto scriptElem = elem->FirstChildElement(); scriptElem != NULL; scriptElem = scriptElem->NextSiblingElement()) {
    Logger::instance()->log(scriptElem->Value());
    std::string trigger = scriptElem->Attribute("trigger");
    if (trigger == "timer") {
      int triggerTime = std::stoi(scriptElem->Attribute("trigger-time"));
      et->addTimerTriggeredScript(triggerTime, buildScriptFromBody(scriptElem));
    } else if (trigger == "click") {
      et->setOnClickScript(buildScriptFromBody(scriptElem));
    } else if (trigger == "mouse-over") {
      et->setOnMouseOverScript(buildScriptFromBody(scriptElem));
    }
  }
}

bool StateParser::parseObjects(TiXmlElement *root, std::vector<GameObject*> *gameObjects) {
    for (auto elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        GameObjectParams *params = new GameObjectParams();
        for (auto attr = elem->FirstAttribute(); attr != NULL; attr = attr->Next()) {
            std::string key = attr->Name();
            std::string value = attr->Value();
            params->addParam(key, value);
        }
        Logger::instance()->log("Creating:");
        Logger::instance()->log(elem->Attribute("type"));
        GameObject* gameObject = GameObjectFactory::instance()->create(elem->Attribute("type"));
        for (auto childElem = elem->FirstChildElement(); childElem != NULL; childElem = childElem->NextSiblingElement()) {
            if (std::string(childElem->Value()) == "boxes") {
                if (MouseInteractable *mi = dynamic_cast<MouseInteractable*>(gameObject)) {
                    addClickBoxes(mi, childElem);
                }
            }
        }
        gameObject->load(params);
        gameObjects->push_back(gameObject);
    }
    return true;
}

bool StateParser::parseTextures(TiXmlElement* root, std::vector<std::string> *textureIds) {
    for (auto elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        std::string fileName = elem->Attribute("fileName");
        std::string id = elem->Attribute("id");
        textureIds->push_back(id);
        TextureManager::instance()->load(fileName, id, Game::instance()->getRenderer());
    }
    return true;
}

bool StateParser::parseGameState(TiXmlElement *root, GameObjectParams *gameState) {
    for (auto elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        std::string key = std::string(elem->Value());
        std::string value = std::string(elem->GetText());
        gameState->addParam(key, value);
    }
    return true;
}

void StateParser::parseConfig(ConfigParams *config) {
    TiXmlDocument xmlDoc;
    if (!xmlDoc.LoadFile("assets/conf.xml")) {
        std::cerr << xmlDoc.ErrorDesc() << std::endl;
    }
    TiXmlElement *root = xmlDoc.RootElement();
    for (auto elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        std::string key = elem->Value();
        std::string value = elem->GetText();
        config->addParam(key, value);
    }
}
