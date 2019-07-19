#include <InputHandler.h>
#include <iostream>

InputHandler* InputHandler::_instance = 0;

InputHandler::~InputHandler() {
}


bool InputHandler::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        handleMouseButtonEvents(&event);
        handleMouseMotionEvents(&event);
        handleKeyboardState(&event);
    }
    return true;
}

void InputHandler::handleKeyboardState(SDL_Event *event) {
    _keyState = SDL_GetKeyboardState(&_keyStateLength);
}

bool InputHandler::isKeyDown(SDL_Scancode key) {
    if (_keyState == NULL || key > _keyStateLength) return false;
    bool result = _keyState[key] == 1;
    if (result) {
      pressedKeys[key] = Ticker::instance()->ticks();
    }
    return result;
}

bool InputHandler::isKeyPressed(SDL_Scancode key) {
  if (_keyState == NULL || key > _keyStateLength) return false;
  bool result = _keyState[key] == 1;
  if (result) {
    if (pressedKeys.find(key) != pressedKeys.end()) {
      if (Ticker::instance()->ticks() - pressedKeys[key] < ticksInThirdOfSecond) {
	return false;
      }
    }
    pressedKeys[key] = Ticker::instance()->ticks();
    return true;
  }
  return false;
}

void InputHandler::handleMouseMotionEvents(SDL_Event *event) {
    if(event->type == SDL_MOUSEMOTION) {
        _mousePosition->setX(event->motion.x);
        _mousePosition->setY(event->motion.y);
    }
}

void InputHandler::handleMouseButtonEvents(SDL_Event *event) {
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        if (event->button.button == SDL_BUTTON_LEFT)
        {
            _mouseButtonState[LEFT] = true;
        }
        if (event->button.button == SDL_BUTTON_MIDDLE)
        {
            _mouseButtonState[MIDDLE] = true;
        }
        if (event->button.button == SDL_BUTTON_RIGHT)
        {
            _mouseButtonState[RIGHT] = true;
        }
    }
    if (event->type == SDL_MOUSEBUTTONUP) {
        if (event->button.button == SDL_BUTTON_LEFT)
        {
            _mouseButtonState[LEFT] = false;
        }
        if (event->button.button == SDL_BUTTON_MIDDLE)
        {
            _mouseButtonState[MIDDLE] = false;
        }
        if (event->button.button == SDL_BUTTON_RIGHT)
        {
            _mouseButtonState[RIGHT] = false;
        }
    }
}
