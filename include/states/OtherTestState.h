#include "GameState.h"

class OtherTestState: public GameState {
    public:
        ~OtherTestState();
        bool update(bool isTopState = false);
        void render(SDL_Renderer *renderer);
        
        bool onEnter();
        bool onExit();
        std::string getStateId() const {
            return stateId;
        }
    private:
        static const std::string stateId;
};