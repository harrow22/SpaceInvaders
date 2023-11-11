#ifndef SPACEINVADERS_SPEAKER_H
#define SPACEINVADERS_SPEAKER_H

#include <cstdint>
#include <string>
#include <filesystem>
#include "SDL_mixer.h"

class Speaker {
public:
    explicit Speaker(const std::string& env)
    {
        const std::string dir {env + "/../../assets/sound/"};
        const std::string format {".wav"};
        const std::string soundFiles[2][len] {
                {"0", "3", "2", "1", "9","4", "5", "6", "7", "8"},
                {
                 "ufo_highpitch",
                 "shoot",
                 "explosion",
                 "invaderkilled",
                 "extendedplay",
                 "fastinvader1",
                 "fastinvader2",
                 "fastinvader3",
                 "fastinvader4",
                 "ufo_lowpitch"}
        };

        int loaded {0};
        for (int i {0}; i != len; ++i) {
            std::string path {};
            if (std::filesystem::exists(dir + soundFiles[0][i] + format))
                path = dir + soundFiles[0][i] + format;
            else if (std::filesystem::exists(dir + soundFiles[1][i] + format))
                path = dir + soundFiles[1][i] + format;

            if (!path.empty())
                sound[i] = Mix_LoadWAV(path.c_str());
        }
    }
    void play(std::uint8_t);
    void off();
private:
    static constexpr int len {10};
    Mix_Chunk* sound[9] {};
};


#endif //SPACEINVADERS_SPEAKER_H
