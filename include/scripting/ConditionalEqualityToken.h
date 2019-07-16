#ifndef CONDITIONAL_EQUALITY_TOKEN
#define CONDITIONAL_EQUALITY_TOKEN

#include <ConfigParams.h>
#include <scripting/ConditionalToken.h>
#include <string>

class ConditionalEqualityToken : public ConditionalToken {
 public:
  ConditionalEqualityToken(std::string key, std::string value, bool equals) : _key(key), _value(value), _equals(equals) {}
 protected:
  bool test() {
    return ((ConfigParams::instance()->get(_key) == _value) == _equals);
  }
 private:
  std::string _key, _value;
  bool _equals;
  
};

#endif
