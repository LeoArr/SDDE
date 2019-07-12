#ifndef GAME_OBJECT_FACTORY
#define GAME_OBJECT_FACTORY

#include <objects/Player.h>
#include <objects/Wall.h>
#include <objects/Cursor.h>
#include <objects/Prop.h>
#include <string.h>

enum GameObjectEnum {
    _PLAYER,
    _WALL,
    _CURSOR,
    _PROP,
    NO_OBJ
};

class GameObjectFactory {
    public:
        static GameObjectFactory* instance() {
            if (_instance == 0) {
                _instance = new GameObjectFactory();
            }
            return _instance;
        }
        GameObject* create(std::string typeId) {
            switch (getObjectTypeEnum(typeId))
            {
                case GameObjectEnum::_PLAYER:
                    return new Player();
                case GameObjectEnum::_WALL:
                    return new Wall();
                case GameObjectEnum::_CURSOR:
                    return new Cursor();
                case GameObjectEnum::_PROP:
                    return new Prop();
                default:
                    return NULL;
            }
        }

        static GameObjectEnum getObjectTypeEnum(std::string typeName) {
            if (typeName == "Player") return GameObjectEnum::_PLAYER;
            if (typeName == "Wall") return GameObjectEnum::_WALL;
            if (typeName == "Cursor") return GameObjectEnum::_CURSOR;
            if (typeName == "Prop") return GameObjectEnum::_PROP;
            return GameObjectEnum::NO_OBJ;
        }
    private:
        static GameObjectFactory* _instance;
};

#endif
