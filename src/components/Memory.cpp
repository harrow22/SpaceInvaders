#include "Memory.h"
#include <iostream>
#include <format>
#include <fstream>

static constexpr int mirror {0x3FFF};

void Memory::write(std::uint16_t addr, const std::uint8_t data)
{
    addr &= mirror;

    if (addr >= rom.size())
        addr < ram.size() ? ram[addr] = data : vram[addr] = data;
    else
        std::cerr << "error: attempt to write to read-only memory";
}

std::uint8_t Memory::read(std::uint16_t addr) const
{
    addr &= mirror;

    if (addr < rom.size())
        return rom[addr];
    else if (addr < ram.size())
        return ram[addr];
    else if (addr < vram.size())
        return vram.size();

    // should never get here
    return 0;
}

bool Memory::loadRom(std::string rom, int addr)
{
    std::ifstream file {"assets/roms/" + rom, std::ios::binary};

    if (file.fail()) {
        std::cerr << std::format("error: failure when opening file '{:s}'.\n", rom);
        return false;
    }

    if (!file.is_open()) {
        std::cerr << std::format("error: can't open file '{:s}'. Ensure you're in the correct directory: SpaceInvaders/\n", rom);
        return false;
    }

    file.read(reinterpret_cast<char*>(&rom[addr]), rom.size());

    if (file.fail()) {
        std::cerr << std::format("error: failed when reading file '{:s}'.\n", rom);
        return false;
    }

    return true;
}
