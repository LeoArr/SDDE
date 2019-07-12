#include <TextureManager.h>
#include <iostream>

TextureManager* TextureManager::_instance = 0;

TextureManager::~TextureManager() {
    for (auto it=textureMap.begin(); it!=textureMap.end(); ++it)
        textureMap.erase(it);
    delete _instance;
}

void setRectDimensions(SDL_Rect* srcRect, SDL_Rect *destRect,
                        int x, int y, int width, int height, float scale, int curFrame = 0, int curRow = 0) {
    srcRect->x = width * curFrame;
    srcRect->y = height * curRow;
    srcRect->w = width;
    srcRect->h = height;

    destRect->x = x;
    destRect->y = y;
    destRect->w = ((int) width * scale);
    destRect->h = ((int) height * scale);
}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer *renderer) {
    SDL_Surface* tempSurface = IMG_Load(("assets/" + fileName).c_str());
    if(tempSurface == 0)
        return false;

    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    if(newTexture != 0) {
        textureMap[id] = newTexture;
        return true;
    }
    return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, int curRow, int curFrame,
                            float zoom, SDL_Renderer *renderer, SDL_RendererFlip flip) {
    SDL_Rect srcRect, destRect;
    // setRectDimensions(&srcRect, &destRect, x, y, width, height, 1);
    setRectDimensions(&srcRect, &destRect, x, y, width, height, zoom, curFrame, curRow);
    SDL_RenderCopyEx(renderer, textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int curRow, int curFrame,
                    float zoom, SDL_Renderer *renderer, SDL_RendererFlip flip) {
    SDL_Rect srcRect, destRect;
    setRectDimensions(&srcRect, &destRect, x, y, width, height, zoom, curFrame, curRow);
    SDL_RenderCopyEx(renderer, textureMap[id], &srcRect, &destRect, 0, 0, flip);
}
