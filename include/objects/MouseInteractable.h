#ifndef MOUSE_INTERACTABLE
#define MOUSE_INTERACTABLE

#include <InputHandler.h>
#include <utils/Vector2D.h>
#include <Game.h>
#include <algorithm>
#include <vector>

class ClickBox {
    public:
        ClickBox(Vector2D *pos, int width, int height) :
            _pos(pos), _width(width), _height(height) {}
        Vector2D *_pos;
        int _width, _height;
        bool isInside(Vector2D *parentPos, Vector2D *vec) {
            if (vec->getX() < parentPos->getX() + _pos->getX())
                return false;
            if (vec->getX() > parentPos->getX() + _pos->getX() + _width)
                return false;
            if (vec->getY() < parentPos->getY() + _pos->getY())
                return false;
            if (vec->getY() > parentPos->getY() + _pos->getY() + _height)
                return false;
            return true;
        }

        void draw(Vector2D *parentPos, SDL_Renderer *renderer) {
            SDL_Point points[5] = {
                {(int)(parentPos->getX() + _pos->getX()),
                    (int)(parentPos->getY() + _pos->getY())},
                {(int)(parentPos->getX() + _pos->getX() + _width),
                    (int)(parentPos->getY() + _pos->getY())},
                {(int)(parentPos->getX() + _pos->getX() + _width),
                    (int)(parentPos->getY() + _pos->getY() + _height)},
                {(int)(parentPos->getX() + _pos->getX()),
                    (int)(parentPos->getY() + _pos->getY() + _height)},
                {(int)(parentPos->getX() + _pos->getX()),
                    (int)(parentPos->getY() + _pos->getY())}
            };
            SDL_RenderDrawLines(renderer, points, 5);
        }
};

class MouseInteractable {
    public:
        virtual void onClick() = 0;
        virtual void onMouseOver() = 0;
	bool isClicked(Vector2D *mousePos) {
	  return isClickedInternal(mousePos);
	}
        bool isMouseOvered(Vector2D *mousePos) {
	  return isMouseOveredInternal(mousePos);
	}
        virtual void addClickBox(ClickBox *box) {
            _clickBoxes.push_back(box);
        }
        ~MouseInteractable() {
            for (auto box : _clickBoxes) {
                delete box;
            }
            _clickBoxes.clear();
        }
	void update(Vector2D *parentPos) {
	  _ownerPosition = parentPos;
	  Vector2D *mousePos = InputHandler::instance()->getMousePosition();
	  if (isClicked(mousePos)) {
	    onClick();
	  }
	  if (isMouseOvered(mousePos)) {
	    onMouseOver();
	  }
	}
    protected:
        MouseInteractable() {}
        std::vector<ClickBox*> _clickBoxes;
        virtual bool isClickedInternal(Vector2D *mousePos) {
            return InputHandler::instance()->getMouseButtonState(MouseButton::LEFT) &&
                isMouseOveredInternal(mousePos);
        }
        virtual bool isMouseOveredInternal(Vector2D *mousePos) {
            return std::any_of(_clickBoxes.begin(), _clickBoxes.end(),
			       [this, mousePos](auto box) {
				 return box->isInside(_ownerPosition, mousePos);
			       });
        }
        virtual void drawBoxes() {
            auto renderer = Game::instance()->getRenderer();
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
            for (auto box : _clickBoxes) {
                box->draw(_ownerPosition, renderer);
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        }
 private:
	Vector2D *_ownerPosition;
};

#endif
