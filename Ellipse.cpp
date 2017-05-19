//
// Created by skala on 14.5.17.
//

#include <cmath>
#include "Ellipse.h"

Ellipse::Ellipse(float x, float y, int width, int height, Color Stroke) :
        Shape(x, y, Stroke), width_(width), height_(height) {}

void Ellipse::Render(int16_t display[320][480]) {
    if (!IsVisible) return;

    int height = (int) ceil((double) height_ / 2.0);
    for (int y = -height; y <= height; y++) {
        for (int x = -width_; x <= width_; x++) {
            if (x * x * height * height + y * y * width_ * width_ <= height * height * width_ * width_)
                if (InsideDisplay((int) (x_ + x), (int) (y_ + y)))
                    display[(int) (y_ + y)][(int) (x_ + x)] = stroke_.getRGB565();
        }
    }
}

Ellipse::Ellipse() {

}
