#ifndef GAME_OBJECT_PARAMS
#define GAME_OBJECT_PARAMS

#include <string>
#include <map>

class GameObjectParams {
    public:
        virtual std::string get(std::string key) const {
            auto value = _paramsMap.find(key);
            if (value != _paramsMap.end())
                return value->second;
            return "";
        }

        virtual int getI(std::string key) const {
            auto value = _paramsMap.find(key);
            if (value != _paramsMap.end())
                return std::stoi(value->second);
            return 0;
        }

        virtual void addParam(std::string key, std::string value) {
            _paramsMap[key] = value;
        }

        virtual ~GameObjectParams() {}

    protected:
        std::map<std::string, std::string> _paramsMap;
};

#endif