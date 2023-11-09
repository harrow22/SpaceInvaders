#include "Keyboard.h"
#include <utility>

void Keyboard::onKeyDown(SDL_Scancode scancode)
{
    switch (scancode) {
        case SDL_SCANCODE_2: input1 |= twoPlayer;
        case SDL_SCANCODE_1: input1 |= onePlayer;
        case SDL_SCANCODE_SPACE: input1 |= p1shot;
        case SDL_SCANCODE_A: input1 |= p1left;
        case SDL_SCANCODE_D: input1 |= p1right;
        case SDL_SCANCODE_T: input2 |= tilt;
        case SDL_SCANCODE_RSHIFT: input2 |= p2shot;
        case SDL_SCANCODE_LEFT: input2 |= p2left;
        case SDL_SCANCODE_RIGHT: input2 |= p2right;
        default: break;
    }

}

void Keyboard::onKeyUp(SDL_Scancode scancode)
{
    switch (scancode) {
        case SDL_SCANCODE_2: input1 &= ~twoPlayer;
        case SDL_SCANCODE_1: input1 &= ~onePlayer;
        case SDL_SCANCODE_SPACE: input1 &= ~p1shot;
        case SDL_SCANCODE_A: input1 &= ~p1left;
        case SDL_SCANCODE_D: input1 &= ~p1right;
        case SDL_SCANCODE_T: input2 &= ~tilt;
        case SDL_SCANCODE_RSHIFT: input2 &= ~p2shot;
        case SDL_SCANCODE_LEFT: input2 &= ~p2left;
        case SDL_SCANCODE_RIGHT: input2 &= ~p2right;
        default: break;
    }
}
