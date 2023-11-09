#ifndef SPACEINVADERS_MEMORY_H
#define SPACEINVADERS_MEMORY_H

#include <cstdint>
#include <array>
#include <string>

class Memory {
public:
    Memory()
    {
        // loading the roms
        const std::string romPrefix {"invaders."};
        const char romSuffix[4] {'h', 'g', 'f', 'e'};
        const int addr[4] {0x0, 0x800, 0x1000, 0x1800};

        for (int i {0}; i != 4; ++i)
            if (!loadRom(romPrefix + romSuffix[i], addr[i])) return;

        romLoaded = true;
    }

    void write(std::uint16_t, std::uint8_t);
    [[nodiscard]] std::uint8_t read(std::uint16_t) const;

    std::array<std::uint8_t, 0x3FFF - 0x2400 + 1> vram {};
    bool romLoaded {false};
private:
    /* Memory map:
     *  0000-1FFF 8K ROM
     *  2000-23FF 1K RAM
     *  2400-3FFF 7K Video RAM
     *  4000- RAM mirror
     */

    static constexpr int ramStart {0x2000};
    static constexpr int vramStart {0x2400};
    static constexpr int mirror {0x3FFF};

    std::array<std::uint8_t, 0x1FFF - 0 + 1> rom {};
    std::array<std::uint8_t, 0x23FF - 0x2000 + 1> ram {};
    bool loadRom(std::string, int);
};


#endif //SPACEINVADERS_MEMORY_H
