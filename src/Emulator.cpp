#include <string_view>
#include <algorithm>
#include <format>
#include "SDL.h"
#include "Intel8080.h"
#include "components/Memory.h"
#include "components/IO.h"
#include "components/Display.h"
#include "components/Keyboard.h"

void onInterrupt(Intel8080& intel8080, std::uint8_t resetVector)
{
    // tick past T2
    intel8080.tick();

    // clear the INT line
    intel8080.pins &= ~Intel8080::INT;

    // "force" the reset instruction onto the intel8080's data bus
    intel8080.setDBus(resetVector);
}

void onDataIn(Intel8080& intel8080, Memory& memory, IO& io)
{
    switch(intel8080.status) {
        case Intel8080::instructionFetch: case Intel8080::memoryRead: case Intel8080::stackRead:
            intel8080.setDBus(memory.read(intel8080.getABus()));
            break;
        case Intel8080::inputRead:
            intel8080.setDBus(io.read(intel8080.getABus()));
            break;
    }
}

void onDataOut(Intel8080& intel8080, Memory& memory, IO& io)
{
    switch(intel8080.status) {
        case Intel8080::memoryWrite: case Intel8080::stackWrite:
            memory.write(intel8080.getABus(), intel8080.getDBus());
            break;
        case Intel8080::outputWrite:
            io.write(intel8080.getABus(), intel8080.getDBus());
            break;
    }
}

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
        SDL_Log("SDL_Init() failed. SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // clock speed is technically 2 mhz but setting it to 1 here because I need to run the loop twice for both interrupts
    static constexpr int clockSpeed {static_cast<int>(1e6)};
    static constexpr std::uint8_t rst[2] {0xCF, 0xD7};
    std::uint8_t resetVector {};
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

    // quit=false if the display initialized correctly and roms were successfully loaded; otherwise quit=true
    bool quit {!(display.active and memory.romLoaded)};
    intel8080.reset();
    memory.loadHighScore();
    while (!quit) {
        // process SDL events
        SDL_Event e;
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
                if (intel8080.pins & Intel8080::SYNC and intel8080.pins & Intel8080::INTA) {
                    onInterrupt(intel8080, resetVector);
                } else if (intel8080.pins & Intel8080::DBIN)
                    onDataIn(intel8080, memory, io);
                else if (intel8080.pins & Intel8080::WR)
                    onDataOut(intel8080, memory, io);
            }
            // generate interrupt
            intel8080.pins |= Intel8080::INT;
            resetVector = rst[half];
        }

        // draw a frame
        display.draw(memory.vram);

        // sleep until the next frame accounting for spent time
        SDL_Delay(std::max(0LL, frameTime - static_cast<long long>(SDL_GetTicks64() - begin)));
    }

    // user exited the window
    memory.saveHighScore();
    display.off();
    SDL_Quit();
    return 0;
}
