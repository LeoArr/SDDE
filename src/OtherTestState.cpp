#include <states/OtherTestState.h>
#include <iostream>

const std::string OtherTestState::stateId = "OtherTestState";

OtherTestState::~OtherTestState() {
    std::cout << "Destroying OtherTestState: " + getStateId() << std::endl;
}

void OtherTestState::render(SDL_Renderer *renderer) {
}

bool OtherTestState::update(bool isTopState) {
    return true;
}

bool OtherTestState::onEnter() {
    return true;
}

bool OtherTestState::onExit() {
    return true;
}