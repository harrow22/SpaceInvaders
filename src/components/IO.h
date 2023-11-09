#ifndef SPACEINVADERS_IO_H
#define SPACEINVADERS_IO_H

#include <cstdint>
#include "Speaker.h"
#include "Keyboard.h"

class IO {
public:
    explicit IO(Keyboard& kb) : keyboard{kb} { }

    std::uint8_t read(std::uint8_t);
    void write(std::uint8_t, std::uint8_t);
private:
    // INP0: mapped but never used
    static std::uint8_t inp0() { return 0b1110; }

    // INP1: inputs
    std::uint8_t inp1() { return keyboard.input1; }

    // INP2: inputs
    std::uint8_t inp2() { return keyboard.input2; }

    // SHFT_IN: bit shift register read
    std::uint8_t shftIn() { return (r >> (8 - offset)) & 0xFF; }

    // SHIFTAMNT: shift amount (3 bits)
    void shftAmnt(std::uint8_t data) { offset = data & 0b111; }

    // SHFT_DATA: shift data
    void shftData(std::uint8_t data) { r = (r >> 8) | (data << 8); }

    // SOUND1: sound bits
    // SOUND2: sound bits
    void sound(std::uint8_t, int loc=0);

    // WATCHDOG: watch-dog
    void watchdog(std::uint8_t) { }

    // hardware shift register
    std::uint16_t r {0};
    std::uint8_t offset {0};

    Speaker speaker {};
    Keyboard& keyboard;
};


#endif //SPACEINVADERS_IO_H
