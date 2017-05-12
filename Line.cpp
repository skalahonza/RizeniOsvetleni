//
// Created by skala on 12.5.17.
//

#include <cmath>
#include "Line.h"

unsigned short Line::getX2() const {
    return x2_;
}

unsigned short Line::getY2() const {
    return y2_;
}

Line::Line(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, Color stroke)
        : stroke_(stroke), x2_(x2), y2_(y2) {
    x_ = x1;
    y_ = y1;
    IsVisible = true;
}

void Line::Render(__uint16_t display[320][480]) {
    if (!IsVisible)
        return;

    int vx = x2_ - x_;// vector x
    int vy = y2_ - y_;// vector y
    int length = (int) sqrt(vx * vx + vy * vy); // vector size

    for (int i = 0; i < length; ++i) {
        //display[y_ + length * ()]
    }
}

