#include <string_view>
#include <algorithm>
#include <format>
#include "SDL.h"
#include "Intel8080.h"
#include "components/Memory.h"
#include "components/IO.h"
#include "components/Display.h"
#include "components/Keyboard.h"

#ifndef NDEBUG
#include <string>
#include <iostream>

static constexpr std::string disassambleTable[256] = {
        "nop", "lxi b,#", "stax b", "inx b",
        "inr_ b", "dcr_ b", "mvi b,#", "rlc", "ill", "dad b", "ldax b", "dcx b",
        "inr_ c", "dcr_ c", "mvi c,#", "rrc", "ill", "lxi d,#", "stax d", "inx d",
        "inr_ d", "dcr_ d", "mvi d,#", "ral", "ill", "dad d", "ldax d", "dcx d",
        "inr_ e", "dcr_ e", "mvi e,#", "rar", "ill", "lxi h,#", "shld", "inx h",
        "inr_ h", "dcr_ h", "mvi h,#", "daa", "ill", "dad h", "lhld", "dcx h",
        "inr_ l", "dcr_ l", "mvi l,#", "cma", "ill", "lxi sp,#", "sta $", "inx sp",
        "inr_ M", "dcr_ M", "mvi M,#", "stc", "ill", "dad sp", "lda $", "dcx sp",
        "inr_ a", "dcr_ a", "mvi a,#", "cmc", "mov b,b", "mov b,c", "mov b,d",
        "mov b,e", "mov b,h", "mov b,l", "mov b,M", "mov b,a", "mov c,b", "mov c,c",
        "mov c,d", "mov c,e", "mov c,h", "mov c,l", "mov c,M", "mov c,a", "mov d,b",
        "mov d,c", "mov d,d", "mov d,e", "mov d,h", "mov d,l", "mov d,M", "mov d,a",
        "mov e,b", "mov e,c", "mov e,d", "mov e,e", "mov e,h", "mov e,l", "mov e,M",
        "mov e,a", "mov h,b", "mov h,c", "mov h,d", "mov h,e", "mov h,h", "mov h,l",
        "mov h,M", "mov h,a", "mov l,b", "mov l,c", "mov l,d", "mov l,e", "mov l,h",
        "mov l,l", "mov l,M", "mov l,a", "mov M,b", "mov M,c", "mov M,d", "mov M,e",
        "mov M,h", "mov M,l", "hlt", "mov M,a", "mov a,b", "mov a,c", "mov a,d",
        "mov a,e", "mov a,h", "mov a,l", "mov a,M", "mov a,a", "add_ b", "add_ c",
        "add_ d", "add_ e", "add_ h", "add_ l", "add_ M", "add_ a", "adc_ b", "adc_ c",
        "adc_ d", "adc_ e", "adc_ h", "adc_ l", "adc_ M", "adc_ a", "sub_ b", "sub_ c",
        "sub_ d", "sub_ e", "sub_ h", "sub_ l", "sub_ M", "sub_ a", "sbb_ b", "sbb_ c",
        "sbb_ d", "sbb_ e", "sbb_ h", "sbb_ l", "sbb_ M", "sbb_ a", "ana_ b", "ana_ c",
        "ana_ d", "ana_ e", "ana_ h", "ana_ l", "ana_ M", "ana_ a", "xra_ b", "xra_ c",
        "xra_ d", "xra_ e", "xra_ h", "xra_ l", "xra_ M", "xra_ a", "ora_ b", "ora_ c",
        "ora_ d", "ora_ e", "ora_ h", "ora_ l", "ora_ M", "ora_ a", "cmp_ b", "cmp_ c",
        "cmp_ d", "cmp_ e", "cmp_ h", "cmp_ l", "cmp_ M", "cmp_ a", "rnz", "pop b",
        "jnz $", "jmp $", "cnz $", "push b", "adi #", "rst 0", "rz", "ret", "jz $",
        "ill", "cz $", "call $", "aci #", "rst 1", "rnc", "pop d", "jnc $", "out p",
        "cnc $", "push d", "sui #", "rst 2", "rc", "ill", "jc $", "in p", "cc $",
        "ill", "sbi #", "rst 3", "rpo", "pop h", "jpo $", "xthl", "cpo $", "push h",
        "ani_ #", "rst 4", "rpe", "pchl", "jpe $", "xchg", "cpe $", "ill", "xri #",
        "rst 5", "rp", "pop psw", "jp $", "di", "cp $", "push psw", "ori #",
        "rst 6", "rm", "sphl", "jm $", "ei", "cm $", "ill", "cpi #", "rst 7"};

void log(Intel8080& intel8080, Memory& memory, std::string cyc)
{
    bool fetch {static_cast<bool>(intel8080.pins & Intel8080::M1)};
    std::cout << std::format(
                    "{:s}:\tPC: {:0>4X}, AF: {:0>4X}, BC: {:0>4X}, DE: {:0>4X}, HL: {:0>4X}, SP: {:0>4X}, ABUS: {:0>4X}, DBUS: {:0>2X}\t({:0>2X} {:0>2X} {:0>2X} {:0>2X}) - {:s}\n",
                    cyc,
                    intel8080.pc,
                    intel8080.getReg(Intel8080::A) << 8U | intel8080.getReg(Intel8080::F),
                    intel8080.getPair(Intel8080::BC),
                    intel8080.getPair(Intel8080::DE),
                    intel8080.getPair(Intel8080::HL),
                    intel8080.getPair(Intel8080::SP),
                    intel8080.getABus(),
                    intel8080.getDBus(),
                    memory.read(intel8080.pc),
                    memory.read(intel8080.pc + 1U),
                    memory.read(intel8080.pc + 2U),
                    memory.read(intel8080.pc + 3U),
                    disassambleTable[fetch ? memory.read(intel8080.pc) : intel8080.ir]);
}
#endif

void onDataIn(Intel8080& intel8080, Memory& memory, IO& io)
{
    switch(intel8080.status) {
        case Intel8080::instructionFetch: case Intel8080::memoryRead: case Intel8080::stackRead:
            intel8080.setDBus(memory.read(intel8080.getABus()));
#ifndef NDEBUG
            log(intel8080, memory, "MEM READ");
#endif
            break;
        case Intel8080::inputRead:
            intel8080.setDBus(io.read(intel8080.getABus()));
#ifndef NDEBUG
            log(intel8080, memory, "INPUT READ");
#endif
            break;
    }
}

void onDataOut(Intel8080& intel8080, Memory& memory, IO& io)
{
    switch(intel8080.status) {
        case Intel8080::memoryWrite: case Intel8080::stackWrite:
            memory.write(intel8080.getABus(), intel8080.getDBus());
#ifndef NDEBUG
            log(intel8080, memory, "MEM WRITE");
#endif
            break;
        case Intel8080::outputWrite:
            io.write(intel8080.getABus(), intel8080.getDBus());
#ifndef NDEBUG
            log(intel8080, memory, "IO WRITE");
#endif
            break;
    }
}

void interrupt(Intel8080& intel8080, Memory& memory, std::uint8_t vector)
{
    // assert the INT line
    intel8080.pins |= Intel8080::INT;

    // tick the cpu until it acknowledges the interrupt
    do {
        intel8080.tick();
    } while (!(intel8080.pins & Intel8080::INTA));

    // complete T2
    intel8080.tick();

    // clear the INT line
    intel8080.pins &= ~Intel8080::INT;

    // "force" the reset instruction onto the intel8080's data bus
    intel8080.setDBus(vector);

    // tick the cpu for the remainder of the RST instruction
    for (int i {0}; i != 9; ++i)
        intel8080.tick();
}

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("SDL_Init() failed. SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // clock speed is technically 2 mhz but setting it to 1 here because I need to run the loop twice for both interrupts
    static constexpr int clockSpeed {static_cast<int>(1e6)};
    static constexpr std::uint8_t rst[2] {0xCF, 0xD7};
    const int frameTime {static_cast<int>(std::ceil(1.0 / 60.0 * 1e3))};

    // DIP switch command line parsing
    std::uint8_t dipswitch {0};
    using namespace std::string_view_literals;
    for (int i {1}; i < argc; ++i) {
        bool hasNext {i + 1 != argc};

        if (argv[i] == "-ships"sv and hasNext) {
            try {
                std::string n {argv[++i]};
                switch (std::stoi(n)) {
                    case 4: dipswitch |= 0b01; break;
                    case 5: dipswitch |= 0b10; break;
                    case 6: dipswitch |= 0b11; break;
                }
            } catch (std::exception& e) {
                SDL_Log("error: failed to read integer for '-ships' parameter, using default=3.\n");
            }

        } else if (argv[i] == "-difficulty"sv and hasNext) {
            std::string difficulty {argv[++i]};
            if (difficulty == "EASY")
                dipswitch |= 0b1000U;
        } else {
            SDL_Log("Unrecognized command line argument '%s'.\nAvailable parameters are:\n\tenable logging: -ships <NUMBER in range [3,6]>\n\t-difficulty <NORMAL/EASY (case-sensitive)>\n\n", argv[i]);
        }
    }

    // defining hardware
    Intel8080 intel8080 {};
    Memory memory {};
    Keyboard keyboard {dipswitch};
    IO io {keyboard};
    Display display {};

    // quit=false if the display initialized correctly and roms were
    // successfully loaded; otherwise quit=true
    bool quit {!(display.active and memory.romLoaded)};
    intel8080.reset();
    while (!quit) {
        SDL_Event e;
        // process SDL events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                keyboard.onKeyDown(e.key.keysym.scancode);
            } else if (e.type == SDL_KEYUP) {
                keyboard.onKeyUp(e.key.keysym.scancode);
            }
        }

        // run the emulator
        unsigned long long begin {SDL_GetTicks64()};
        for (int half {0}; half != 2; ++half) {
            int cycles {0};

            while (cycles++ < (clockSpeed / 60)) {
                intel8080.tick();

                // handle intel8080 requests
                if (intel8080.pins & Intel8080::DBIN)
                    onDataIn(intel8080, memory, io);
                else if (intel8080.pins & Intel8080::WR)
                    onDataOut(intel8080, memory, io);
            }
            if (intel8080.pins & Intel8080::INTE)
                interrupt(intel8080, memory, rst[half]);
        }

        // draw a frame
        display.draw(memory.vram);

        // sleep until the next frame accounting for spent time
        SDL_Delay(std::max(0LL, frameTime - static_cast<long long>(SDL_GetTicks64() - begin)));
    }

    // user exited the window, quit sdl
    display.off();
    SDL_Quit();
    return 0;
}
