//
// Created by skala on 23.5.17.
//

#include "Icon.h"

Icon::Icon(int x, int y, uint16_t pixels[256]) : Shape() {
    for (int i = 0; i < 256; ++i) {
        icon_[i] = pixels[i];
    }
    x_ = x;
    y_ = y;
}

void Icon::Render(uint16_t display[320][480]) {
    for (int y = 0; y < 16; ++y) {
        for (int x = 0; x < 16; ++x) {
            if (InsideDisplay((int) (x + x_), (int) (y + y_))) {
                display[(int) (y_ + y)][(int) (x_ + x)] = icon_[y * 16 + x];
            }
        }
    }
}
