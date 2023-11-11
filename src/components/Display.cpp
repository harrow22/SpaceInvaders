#include "Display.h"

void Display::draw(std::array<std::uint8_t, 0x1C00>& vram) {
    for (int i {0}; i != vram.size(); ++i) {
        const std::uint8_t byte{vram[i]};
        const int col {i * 8 / screenHeight_};
        int rowBegin {i * 8 % screenHeight_};

        for (int bit {0}; bit != 8; ++bit, ++rowBegin) {
            const int row {screenHeight_ - rowBegin - 1};

            // applying the color overlay
            unsigned long color {textColor_};
            if (32 <= row) {
                if (row < 64)
                    color = ufoColor_;
                else if (row < 192)
                    color = aliensColor_;
                else if (row < 216)
                    color = barrierColor_;
                else if (row < 239 or (row >= 240 and 25 < col and col < 137))
                    color = shipColor_;
            }

            // transpose the array (rotate 90 degrees counter-clockwise)
            rasterBuffer_[row][col] = (byte >> bit) & 0b1 ? color : screenColor_;
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
