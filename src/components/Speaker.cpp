#include "Speaker.h"

void Speaker::play(std::uint8_t idx)
{
    if (sound[idx] == nullptr) return;
    Mix_PlayChannel(-1, sound[idx], 0);
}

void Speaker::off()
{
    for (int i {0}; i != len; ++i) {
        if (sound[i] != nullptr) {
            Mix_FreeChunk(sound[i]);
            sound[i] = nullptr;
        }
    }
}
