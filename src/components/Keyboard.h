#ifndef SPACEINVADERS_KEYBOARD_H
#define SPACEINVADERS_KEYBOARD_H

#include "SDL.h"
#include <cstdint>

struct Keyboard {
public:
    explicit Keyboard(std::uint8_t dip) { control |= (dip << 8); }

    void onKeyDown(SDL_Scancode);
    void onKeyUp(SDL_Scancode);
    [[nodiscard]] std::uint8_t input1() const { return control & 0xFF; }
    [[nodiscard]] std::uint8_t input2() const { return (control >> 8) & 0xFF; }
private:
    static constexpr std::uint8_t nullkey = -1;
    static constexpr std::uint16_t twoPlayer {0b00000010}; // bit 1 = 2P start (1 if pressed)
    static constexpr std::uint16_t onePlayer {0b00000100}; // bit 2 = 1P start (1 if pressed)
    static constexpr std::uint16_t p1shot {0b00010000}; // bit 4 = P1 shot (1 if pressed)
    static constexpr std::uint16_t p1left {0b00100000}; // bit 5 = P1 left (1 if pressed)
    static constexpr std::uint16_t p1right {0b01000000}; // bit 6 = P1 right (1 if pressed)
    static constexpr std::uint16_t tilt {0b00000100 << 8U}; // bit 2 = Tilt
    static constexpr std::uint16_t p2shot {0b00010000 << 8U}; // bit 4 = P2 shot (1 if pressed)
    static constexpr std::uint16_t p2left {0b00100000 << 8U}; // bit 5 = P2 left (1 if pressed)
    static constexpr std::uint16_t p2right {0b01000000 << 8U}; // bit 6 = P2 right (1 if pressed)

    static std::uint16_t bitmask(SDL_Scancode);
    std::uint16_t control {0b00001001};
};


#endif //SPACEINVADERS_KEYBOARD_H
