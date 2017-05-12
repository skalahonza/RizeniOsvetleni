//
// Created by skala on 12.5.17.
//

#include "Point.h"

Point::Point(float x, float y, Color stroke) : stroke_(stroke_) {
    x_ = x;
    y_ = y;
}

void Point::Render(int16_t display[320][480]) {
    if (!isIsVisible()) return;
    display[(int) y_][(int) x_] = stroke_.getRGB565();
}
