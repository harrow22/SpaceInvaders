#include "Memory.h"
#include <iostream>
#include <format>
#include <fstream>

void Memory::write(std::uint16_t addr, const std::uint8_t data)
{
    addr &= mirror;

    if (addr < ramStart)
        std::cout << "error: attempt to write to read-only memory\n";
    else if (addr < vramStart)
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
