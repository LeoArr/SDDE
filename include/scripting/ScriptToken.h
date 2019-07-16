#ifndef SCRIPT_TOKEN
#define SCRIPT_TOKEN

#include <vector>

class ScriptToken {
 public:
  virtual void run() = 0;
  void addChild(ScriptToken* token) {
    children.push_back(token);
  }
  virtual ~ScriptToken() {
    for (auto child : children) {
      delete child;
    }
    children.clear();
  }

 protected:
  std::vector<ScriptToken*> children;
  
};

#endif
