#include <iostream>
#include "SDL.h"
#include "Intel8080.h"

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    Intel8080 intel8080 {};
    intel8080.tick();

    std::cout << "Hello, World!" << std::endl;

    SDL_Quit();
    return 0;
}
