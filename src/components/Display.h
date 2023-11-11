#ifndef SPACEINVADERS_DISPLAY_H
#define SPACEINVADERS_DISPLAY_H

#include "SDL.h"
#include <array>
#include <cstdint>

class Display {
public:
    Display()
    {
        window_ = SDL_CreateWindow(
                "Space Invaders",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                screenWidth_ * scaleFactor_,
                screenHeight_ * scaleFactor_,
                SDL_WINDOW_SHOWN);
        if (!window_) {
            SDL_Log("SDL_CreateWindow() failed. SDL_Error: %s\n", SDL_GetError());
            return;
        }

        renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC);
        if (!renderer_){
            SDL_Log("SDL_CreateRenderer() failed. SDL_Error: %s\n", SDL_GetError());
            return;
        }

        texture_ = SDL_CreateTexture(renderer_,
                                     SDL_PIXELFORMAT_ABGR8888,
                                     SDL_TEXTUREACCESS_STREAMING,
                                     screenWidth_, screenHeight_);
        if (!texture_){
            SDL_Log("SDL_CreateTexture() failed. SDL_Error: %s\n", SDL_GetError());
            return;
        }

        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);
        SDL_RenderSetLogicalSize(renderer_, screenWidth_, screenHeight_);

        // initialize screen
        SDL_RenderClear(renderer_);
        SDL_RenderPresent(renderer_);

        active = true;
    }
    void draw(std::array<std::uint8_t, 0x1C00>&);
    void off();

    bool active {false};
private:
    /**
     * Color codes are in ABGR format (alpha, blue, green, red).
     * Color overlay:
     * ↑
     * 32px: textColor
     * ↓
     * ↑
     * 32px: ufoColor
     * ↓
     * ↑
     * 128px: aliensColor
     * ↓
     * ↑
     * 24px: barrierColor
     * ↓
     * ↑
     * 23px: alienColor
     * ↓
     * ↑               |       ↑
     * 17px: textColor | 26px←16px→87px: shipColor
     * ↓               |       ↓
     */
    static constexpr unsigned int textColor_ {0xFFFFFFFF}; // default=white
    static constexpr unsigned int ufoColor_ {0xFF2626B2}; // default=red
    static constexpr unsigned int aliensColor_ {0xFFB26384}; // default=purple
    static constexpr unsigned int barrierColor_ {0xFF32CD32}; // default=green
    static constexpr unsigned int shipColor_ {0xFFFFFF00}; // default=cyan
    static constexpr unsigned int screenColor_ {0xFF000000}; // default=black

    // display constants
    static constexpr int screenWidth_ {224};
    static constexpr int screenHeight_ {256};
    static constexpr int scaleFactor_ {3};
    static constexpr int pitch {screenWidth_ * sizeof(std::uint32_t)};

    std::uint32_t rasterBuffer_[screenHeight_][screenWidth_] {};
    SDL_Window* window_ {nullptr};
    SDL_Renderer* renderer_ {nullptr};
    SDL_Texture* texture_ {nullptr};
};


#endif //SPACEINVADERS_DISPLAY_H
