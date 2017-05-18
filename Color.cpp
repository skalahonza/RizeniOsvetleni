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

Color::Color(int r, int g, int b) {
    RGBcolor color;
    color.r = r;
    color.g = g;
    color.b = b;
    rgb888_ = color;
    rgb565_ = (int16_t) ((rgb888_.r << 11) | (rgb888_.g << 5) | rgb888_.b);
}

Color::Color() : Color(0, 0, 0) {
}

uint32_t Color::toUINT32() const {
    return (uint32_t) (((rgb888_.r & 0xff) << 16) + ((rgb888_.g & 0xff) << 8) + (rgb888_.b & 0xff));
}

Color Color::fromUINT32(uint32_t data) {
    char r = (char) (data >> 16);
    char g = (char) (data >> 8);
    char b = (char) (data);
    return Color(r, g, b);
}
