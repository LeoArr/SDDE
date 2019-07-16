#ifndef CONDITIONAL_TOKEN
#define CONDITIONAL_TOKEN

#include <scripting/ScriptToken.h>

class ConditionalToken : public ScriptToken {
 public:
  void run() {
    if (test()) {
      for (auto token : children) {
	token->run();
      }
    }
  }
  
 protected:
  virtual bool test() = 0;
};

#endif
