#ifndef CONFIG_PARAMS
#define CONFIG_PARAMS

#include <GameObjectParams.h>

class ConfigParams : public GameObjectParams {
    public:
        static ConfigParams* instance() {
            if (_instance == NULL) {
                _instance = new ConfigParams();
            }
            return _instance;
        }
	~ConfigParams() {
	  delete _instance;
	}
    private:
        ConfigParams() {}
        static ConfigParams* _instance;
};

#endif
