#ifndef SPACEINVADERS_KEYBOARD_H
#define SPACEINVADERS_KEYBOARD_H

#include "SDL.h"
#include <cstdint>

struct Keyboard {
public:
    explicit Keyboard(std::uint8_t dipswitch) : input2{dipswitch} { }

    void onKeyDown(SDL_Scancode);
    void onKeyUp(SDL_Scancode);
    std::uint8_t input1 {0b00001001};
    std::uint8_t input2;
private:
    static constexpr std::uint8_t twoPlayer {0b00000010}; // bit 1 = 2P start (1 if pressed)
    static constexpr std::uint8_t onePlayer {0b00000100}; // bit 2 = 1P start (1 if pressed)
    static constexpr std::uint8_t p1shot {0b00010000}; // bit 4 = P1 shot (1 if pressed)
    static constexpr std::uint8_t p1left {0b00100000}; // bit 5 = P1 left (1 if pressed)
    static constexpr std::uint8_t p1right {0b01000000}; // bit 6 = P1 right (1 if pressed)
    static constexpr std::uint8_t tilt {0b00000100}; // bit 2 = Tilt
    static constexpr std::uint8_t p2shot {0b00010000}; // bit 4 = P2 shot (1 if pressed)
    static constexpr std::uint8_t p2left {0b00100000}; // bit 5 = P2 left (1 if pressed)
    static constexpr std::uint8_t p2right {0b01000000}; // bit 6 = P2 right (1 if pressed)
};


#endif //SPACEINVADERS_KEYBOARD_H
