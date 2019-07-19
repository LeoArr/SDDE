#ifndef EVENT_TRIGGERER
#define EVENT_TRIGGERER

#include <scripting/ConditionalEqualityToken.h>
#include <scripting/LogEventToken.h>
#include <map>

class EventTriggerer {
 public:
  void onClick() {
    if (_onClick != NULL)
      _onClick->run();
  }

  void onMouseOver() {
    if (_onMouseOver != NULL)
      _onMouseOver->run();
  }

  void onTimer(int tick) {
    if (tick > _maxTimerTick)
      return;
    auto script = _timerMap.find(tick);
    if (script != _timerMap.end()) {
      (*script).second->run();
    }
  }

  void setOnClickScript(ScriptToken *script) {
    _onClick = script;
  }

  void setOnMouseOverScript(ScriptToken *script) {
    _onMouseOver = script;
  }

  void addTimerTriggeredScript(int tick, ScriptToken* script) {
    if (tick > _maxTimerTick)
      _maxTimerTick = tick;
    _timerMap[tick] = script;
  }
  
 private:
  int _maxTimerTick;
  ScriptToken *_onClick, *_onMouseOver;
  std::map<int, ScriptToken*> _timerMap;
};

#endif
