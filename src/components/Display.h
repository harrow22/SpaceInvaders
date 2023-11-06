#ifndef SPACEINVADERS_DISPLAY_H
#define SPACEINVADERS_DISPLAY_H

#include "SDL.h"

class Display {
public:
    Display()
    {
        return; // need to do sdl initializations here
        active = true;
    }
    void draw(auto);
    bool active {false};
private:

};


#endif //SPACEINVADERS_DISPLAY_H
