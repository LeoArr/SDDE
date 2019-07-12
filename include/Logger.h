#ifndef LOGGER
#define LOGGER

#define DEBUG

#include <iostream>

class Logger {
    public:
        static Logger* instance() {
            if (_instance == NULL) {
                _instance = new Logger();
            }
            return _instance;
        }
        void log(std::string text) {
#ifdef DEBUG
            std::cout << text << std::endl;
#endif
        }
	void log(int n) {
#ifdef DEBUG
	  std::cout << std::to_string(n) << std::endl;
#endif
	}

    private:
        static Logger *_instance;
};

#endif
