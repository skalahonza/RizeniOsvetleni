//
// Created by skala on 12.5.17.
//

#include "Color.h"

Color::Color(RGBcolor rgb888) {
    rgb888_ = rgb888;
}

RGBcolor Color::getRGB888() const {
    return rgb888_;
}

uint16_t Color::getRGB565() {
    return ((rgb888_.r << 11) | (rgb888_.g << 5) | rgb888_.b);
}

Color::Color(int r, int g, int b) : Color(r, g, b, "") {

}

Color::Color() : Color(0, 0, 0) {
}

uint32_t Color::toUINT32() const {
    return (uint32_t) (((rgb888_.r & 0xff) << 16) + ((rgb888_.g & 0xff) << 8) + (rgb888_.b & 0xff));
}

Color Color::fromUINT32(uint32_t data) {
    unsigned char r = (unsigned char) (char) (data >> 16);
    unsigned char g = (unsigned char) (char) (data >> 8);
    unsigned char b = (unsigned char) (data);
    return Color(r, g, b);
}

Color::Color(int r, int g, int b, std::string name) : name_(name) {
    RGBcolor color;
    color.r = r;
    color.g = g;
    color.b = b;
    rgb888_ = color;
}

const std::string &Color::getName_() const {
    return name_;
}
