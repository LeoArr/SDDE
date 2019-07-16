#ifndef LOG_EVENT_TOKEN
#define LOG_EVENT_TOKEN

#include <scripting/EventToken.h>
#include <Logger.h>
#include <string>

class LogEventToken : public EventToken {
 public:
 LogEventToken(std::string text) : _text(text) {}

 protected:
  void body() {
    Logger::instance()->log(_text);
  }
 private:
  std::string _text;
  
};

#endif
