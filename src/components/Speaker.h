#ifndef SPACEINVADERS_SPEAKER_H
#define SPACEINVADERS_SPEAKER_H

#include <cstdint>

class Speaker {
public:
    Speaker() = default; // need to read sound files here
    void play(std::uint8_t);
private:

};


#endif //SPACEINVADERS_SPEAKER_H
