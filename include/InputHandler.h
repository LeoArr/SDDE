#ifndef INPUT_HANDLER
#define INPUT_HANDLER

#include <utils/Vector2D.h>
#include <ConfigParams.h>
#include <Ticker.h>
#include <SDL2/SDL.h>
#include <map>

enum MouseButton {
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler {
    public:
        static InputHandler* instance() {
            if (_instance == 0) {
                _instance = new InputHandler();
            }
            return _instance;
        }

        bool update();
        ~InputHandler();

        bool getMouseButtonState(Uint8 button) {
            if (button < 0 || button > sizeof(_mouseButtonState)/sizeof(_mouseButtonState[0]) - 1)
                return false;
            return _mouseButtonState[button];
        }

        Vector2D* getMousePosition() {
            return _mousePosition;
        }

        bool isKeyDown(SDL_Scancode key);
	bool isKeyPressed(SDL_Scancode key);

    private:
        InputHandler() : _mousePosition(new Vector2D(0, 0)) {
	  int fps = ConfigParams::instance()->getI("fps");
	  ticksInThirdOfSecond = fps / 3;
	}
        static InputHandler* _instance;
	Uint32 ticksInThirdOfSecond;

        bool _mouseButtonState[3] = {false, false, false};
        void handleMouseButtonEvents(SDL_Event *event);

        Vector2D *_mousePosition;
        void handleMouseMotionEvents(SDL_Event *event);

        const Uint8 *_keyState;
        int _keyStateLength {0};
        void handleKeyboardState(SDL_Event *event);

	std::map<SDL_Scancode, Uint32> pressedKeys;
};

#endif
