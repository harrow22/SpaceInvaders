#include "Keyboard.h"
#include <utility>

void Keyboard::onKeyDown(SDL_Scancode scancode)
{
    switch (scancode) {
        case SDL_SCANCODE_C: input1 |= credit; break;
        case SDL_SCANCODE_2: input1 |= twoPlayer; break;
        case SDL_SCANCODE_1: input1 |= onePlayer; break;
        case SDL_SCANCODE_SPACE: input1 |= p1shot; input2 |= p2shot; break;
        case SDL_SCANCODE_T: input2 |= tilt; break;
        case SDL_SCANCODE_LEFT: input1 |= p1left;; input2 |= p2left; break;
        case SDL_SCANCODE_RIGHT: input1 |= p1right; input2 |= p2right; break;
        default: break;
    }
}

void Keyboard::onKeyUp(SDL_Scancode scancode)
{
    switch (scancode) {
        case SDL_SCANCODE_C: input1 &= ~credit; break;
        case SDL_SCANCODE_2: input1 &= ~twoPlayer; break;
        case SDL_SCANCODE_1: input1 &= ~onePlayer; break;
        case SDL_SCANCODE_SPACE: input1 &= ~p1shot; input2 &= ~p2shot; break;
        case SDL_SCANCODE_T: input2 &= ~tilt; break;
        case SDL_SCANCODE_LEFT: input1 &= ~p1left; input2 &= ~p2left; break;
        case SDL_SCANCODE_RIGHT: input1 &= ~p1right; input2 &= ~p2right; break;
        default: break;
    }
}
