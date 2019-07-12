#include <Game.h>
#include <StateParser.h>
#include <ConfigParams.h>
#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {   
    int i;

    try {
      StateParser::instance()->parseConfig(ConfigParams::instance());
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            std::cerr << "FAILED TO INITIALIZE SDL" << std::endl;
            std::cin >> i;
            return -1;
        }
        if (Game::instance()->init()) {
            while (Game::instance()->isRunning()) {
                Game::instance()->tick();
            }
            delete Game::instance();
            SDL_Quit();
        } else {
            std::cout << "Game failed to initialize" << std::endl;
            std::cin >> i;
            return -1;
        }
    } catch (int e) {
        std::cin >> i;
        std::cout << "Game crashed... Error: " + std::to_string(e) << std::endl;
    }
    return 0;
}

// int WinMain(int argc, char* argv[]) {
//     std::cout << "WinMain" << std::endl;
//     return main(argc, argv);
// } 