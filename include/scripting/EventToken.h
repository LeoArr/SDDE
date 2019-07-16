#ifndef EVENT_TOKEN
#define EVENT_TOKEN

#include <scripting/ScriptToken.h>

class EventToken : public ScriptToken {
 public:
  void run() {
    body();
    for (auto token : children) {
      token->run();
    }
  }
 protected:
  virtual void body() = 0;
  
};

#endif
