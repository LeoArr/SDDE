#ifndef GAME_TEXT_MANAGER
#define GAME_TEXT_MANAGER

#include <TextManager.h>
#include <Ticker.h>
#include <Logger.h>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <SDL2/SDL.h>

struct InfoText {
  SDL_Texture* texture;
  Uint32 addedTick;
  int x, y;
};

class GameTextManager {
 public:
  static GameTextManager* instance() {
    if (_instance == NULL) {
      _instance = new GameTextManager();
    }
    return _instance;
  }

  void addInfoText(std::string textId, std::string text, int x, int y, int ticksOffset = 0) {
    if (infoTexts.find(textId) != infoTexts.end()) {
      infoTexts[textId].addedTick = Ticker::instance()->ticks();
    } else {
      InfoText infoText = {
	TextManager::instance()->textTexture("8bit", text, {255,0,0,0}),
	Ticker::instance()->ticks() + ticksOffset,
	x, y
      };
      infoTexts[textId] = infoText;
    }
  }

  void update() {
    Uint32 ticks = Ticker::instance()->ticks();
    Uint32 maxTicks = 20;
    std::vector<std::string> toErase;
    for (auto text : infoTexts) {
      if (ticks < text.second.addedTick)
	continue;
      if (ticks - text.second.addedTick > maxTicks) {
	toErase.push_back(text.first);
	continue;
      }
      Uint8 alpha = 255 * (1.0f - ((float) ticks - (float) text.second.addedTick) / (float) maxTicks);
      SDL_SetTextureAlphaMod(text.second.texture, alpha);
    }
    for (auto id : toErase) {
      SDL_DestroyTexture(infoTexts[id].texture);
      infoTexts.erase(id);
    }
  }

  void render() {
    for (auto text : infoTexts) {
      TextManager::instance()->draw(text.second.texture, text.second.x, text.second.y);
    }
  }
 private:
  GameTextManager() {};
  static GameTextManager* _instance;

  std::map<std::string, InfoText> infoTexts;
  std::queue<SDL_Texture*> dialogs;
};

#endif
