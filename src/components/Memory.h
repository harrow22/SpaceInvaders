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
        const char romSuffix[4] {'e', 'f', 'g', 'h'};
        const int addr[4] {0x0, 0x800, 0x1000, 0x1800};

        for (int i {0}; i != 4; ++i)
            if (!loadRom(romPrefix + romSuffix[i], addr[i])) return;

        romLoaded = true;
    }

    void write(std::uint16_t, std::uint8_t);
    [[nodiscard]] std::uint8_t read(std::uint16_t) const;

    std::array<std::uint8_t, 0x1BFF> vram {};
    bool romLoaded {false};
private:
    std::array<std::uint8_t, 0x2000> rom {};
    std::array<std::uint8_t, 0x400> ram {};
    static bool loadRom(std::string, int);
};


#endif //SPACEINVADERS_MEMORY_H
