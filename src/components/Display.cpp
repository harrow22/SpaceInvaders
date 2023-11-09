#include "Display.h"

#include <iostream>

void Display::draw(std::array<std::uint8_t, 0x1C00>& vram) {
    for (int i {0}; i != vram.size(); ++i) {
        const std::uint8_t byte{vram[i]};
        const int col {i * 8 / screenHeight_};
        int row {i * 8 % screenHeight_};

        for (int bit {0}; bit != 8; ++bit, ++row) {
            // select the correct color


            // transpose the array (rotate 90 degrees counter-clockwise)
            rasterBuffer_[screenHeight_ - row - 1][col] = (byte >> bit) & 0b1 ? colorOn_ : colorOff_;
        }
    }

    SDL_UpdateTexture(texture_, nullptr, rasterBuffer_, pitch);
    SDL_RenderClear(renderer_);
    SDL_RenderCopy(renderer_, texture_, nullptr, nullptr);
    SDL_RenderPresent(renderer_);
}

void Display::off() {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;
    SDL_DestroyWindow(window_);
    window_ = nullptr;
}
