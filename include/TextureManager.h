#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>

class TextureManager {
public:
    static TextureManager* instance() {
        if (_instance == 0) {
            _instance = new TextureManager();
        }
        return _instance;
    }
    ~TextureManager();

    bool load(std::string fileName, std::string id, SDL_Renderer *renderer);
    
    void draw(std::string id, int x, int y, int width, int height, int curRow, int curFrame,
            float zoom, SDL_Renderer *renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawFrame(std::string id, int x, int y, int width, int height, int curRow, int curFrame,
            float zoom, SDL_Renderer *renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    TextureManager(TextureManager const&) = delete;
    void operator=(TextureManager const&) = delete;
private:
    std::map<std::string, SDL_Texture*> textureMap;
    static TextureManager* _instance;

    TextureManager() {}

};

#endif
