#include "Memory.h"
#include <iostream>
#include <format>
#include <fstream>

void Memory::write(std::uint16_t addr, const std::uint8_t data)
{
    addr &= mirror;

    if (ramStart <= addr and addr < vramStart)
        ram[addr - ramStart] = data;
    else
        vram[addr - vramStart] = data;
}

std::uint8_t Memory::read(std::uint16_t addr) const
{
    addr &= mirror;
    if (addr < ramStart)
        return rom[addr];
    else if (addr < vramStart)
        return ram[addr - ramStart];
    else
        return vram[addr - vramStart];
}

bool Memory::loadRom(std::string path, int addr)
{
    std::ifstream file {"assets/roms/" + path, std::ios::binary};

    if (!file.is_open()) {
        std::cerr << std::format("error: can't open file '{:s}'. Ensure you're in the correct directory: SpaceInvaders/\n", path);
        return false;
    }

    file.read(reinterpret_cast<char*>(&rom[addr]), 0x800);

    if (file.bad()) {
        std::cerr << std::format("error [errno={:d}]: failed when reading file '{:s}'.\n", errno, path);
        return false;
    }

    return true;
}

void Memory::loadHighScore()
{
    if (!romLoaded) return;
    std::ifstream hiscoreFile {"assets/" + hiscorePath, std::ios::binary};

    if (hiscoreFile.is_open()) {
        // see CopyRAMMirror: (https://computerarcheology.com/Arcade/SpaceInvaders/Code.html)
        hiscoreFile.read(reinterpret_cast<char*>(&rom[0x1BF4]), 2);
    }
}

void Memory::saveHighScore()
{
    if (!romLoaded) return;
    std::ofstream hiscoreFile {"assets/" + hiscorePath, std::ios::out};

    if (hiscoreFile.is_open()) {
        // see hiScorL (https://computerarcheology.com/Arcade/SpaceInvaders/RAMUse.html)
        hiscoreFile.write(reinterpret_cast<char*>(&ram[0x20F4 - ramStart]), 2);
    }
}
