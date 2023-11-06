#include "Keyboard.h"
#include <utility>

void Keyboard::onKeyDown(SDL_Scancode scancode)
{
    std::uint16_t key {bitmask(scancode)};
    if (key != nullkey)
        control |= key;
}

void Keyboard::onKeyUp(SDL_Scancode scancode)
{
    std::uint16_t key {bitmask(scancode)};
    if (key != nullkey)
        control &= ~key;
}

std::uint16_t Keyboard::bitmask(SDL_Scancode scancode)
{
    switch (scancode) {
        case SDL_SCANCODE_2: return twoPlayer;
        case SDL_SCANCODE_1: return onePlayer;
        case SDL_SCANCODE_SPACE: return p1shot;
        case SDL_SCANCODE_A: return p1left;
        case SDL_SCANCODE_D: return p1right;
        case SDL_SCANCODE_T: return tilt;
        case SDL_SCANCODE_RSHIFT: return p2shot;
        case SDL_SCANCODE_LEFT: return p2left;
        case SDL_SCANCODE_RIGHT: return p2right;
        default: return nullkey;
    }
}
