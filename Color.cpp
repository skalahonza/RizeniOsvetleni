//
// Created by skala on 12.5.17.
//

#include "Color.h"

Color::Color(RGBcolor rgb888) {
    rgb888_ = rgb888;
    rgb565_ = (u_int16_t) ((rgb888_.r << 11) | (rgb888_.g << 5) | rgb888_.b);
}

RGBcolor Color::getRGB888() {
    return rgb888_;
}

u_int16_t Color::getRGB565() {
    return rgb565_;
}
