#include "IO.h"

std::uint8_t IO::read(std::uint8_t port)
{
    switch (port) {
        case 0: return inp0(); // 0000pr
        case 1: return inp1(); // 0001pr
        case 2: return inp2(); // 0002pr
        case 3: return shftIn(); // 0003pr
        default: return 0; // should never get here
    }
}

void IO::write(std::uint8_t port, std::uint8_t data)
{
    switch (port) {
        case 2: return shftAmnt(data); // 0002pw
        case 3: return sound(data); // 0003pw
        case 4: return shftData(data); // 0004pw
        case 5: return sound(data, 4); // 0005pw
        case 6: return watchdog(data); // 0006pw
        default: break; // should never get here
    }
}

void IO::sound(std::uint8_t data, int loc)
{
    /*
     * sound1:
     *  bit 0=UFO (repeats)        SX0 0.raw
     *  bit 1=Shot                 SX1 1.raw
     *  bit 2=Flash (player die)   SX2 2.raw
     *  bit 3=Invader die          SX3 3.raw
     *  bit 4=Extended play        SX4
     *  bit 5= AMP enable          SX5
     *  bit 6= NC (not wired)
     *  bit 7= NC (not wired)
     *
     * sound2:
     *  bit 0=Fleet movement 1     SX6 4.raw
     *  bit 1=Fleet movement 2     SX7 5.raw
     *  bit 2=Fleet movement 3     SX8 6.raw
     *  bit 3=Fleet movement 4     SX9 7.raw
     *  bit 4=UFO Hit              SX10 8.raw
     *  bit 5= NC (Cocktail mode control ... to flip screen)
     *  bit 6= NC (not wired)
     *  bit 7= NC (not wired)
     */

    for (int bit {0}; bit != 5; ++bit) {
        if (data & bit)
            speaker.play(bit + loc);
    }
}