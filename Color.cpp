//
// Created by skala on 12.5.17.
//

#include "Color.h"

Color::Color(RGBcolor rgb888) {
    rgb888_ = rgb888;
    rgb565_ = (int16_t) ((rgb888_.r << 11) | (rgb888_.g << 5) | rgb888_.b);
}

RGBcolor Color::getRGB888() const {
    return rgb888_;
}

int16_t Color::getRGB565() {
    return rgb565_;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b) {
    RGBcolor color;
    color.r = r;
    color.g = g;
    color.b = b;
    rgb888_ = color;
    rgb565_ = (int16_t) ((rgb888_.r << 11) | (rgb888_.g << 5) | rgb888_.b);
}

Color::Color() : Color(0, 0, 0) {
}
