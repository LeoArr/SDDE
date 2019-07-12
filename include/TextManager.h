#ifndef TEXT_MANAGER
#define TEXT_MANAGER

#include <SDL2/SDL_ttf.h>
#include <Logger.h>
#include <ConfigParams.h>
#include <map>
#include <Game.h>
#include <string>

class TextManager {
 public:
  static TextManager* instance() {
    if (_instance == NULL) {
      _instance = new TextManager();
    }
    return _instance;
  }
  ~TextManager() {
    for (auto font : fonts) {
      TTF_CloseFont(font.second);
    }
    fonts.clear();
    TTF_Quit();
  }

  void load(std::string id, std::string fileName, int ptSize = 8) {
    std::string fileLocation = ConfigParams::instance()->get("assets-folder") +
      ConfigParams::instance()->get("fonts-folder") + fileName;
    if (TTF_Font* font = TTF_OpenFont(fileLocation.c_str(), ptSize)) {
      fonts[id] = font;
    }
  }

  TTF_Font* getFont(std::string id) {
    if (fonts.find(id) != fonts.end()) {
      return fonts[id];
    }
    return NULL;
  }

  SDL_Surface* createTextSurface(std::string fontId, std::string text, SDL_Color color) {
    return TTF_RenderText_Blended_Wrapped(fonts[fontId], text.c_str(), color, 100);
  }

  SDL_Texture* textTexture(std::string id, std::string text, SDL_Color color) {
    SDL_Surface *surface = TextManager::instance()->createTextSurface(id, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::instance()->getRenderer(), surface);
    SDL_FreeSurface(surface);
    return texture;
  }

  void draw(SDL_Texture* texture, int x, int y) {
    SDL_Rect srcRect, destRect;
    srcRect.x = 0;
    srcRect.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);
    destRect.x = x;
    destRect.y = y;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
    SDL_RenderCopyEx(Game::instance()->getRenderer(), texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
  }

 private:
  TextManager() {
    if (TTF_Init() < 0) {
      Logger::instance()->log("Failed to init text");
    }
  }
  static TextManager* _instance;

  std::map<std::string, TTF_Font*> fonts;
};

#endif
