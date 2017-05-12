//
// Created by skala on 12.5.17.
//

#include <cmath>
#include "Line.h"

float Line::getX2() const {
    return x2_;
}

float Line::getY2() const {
    return y2_;
}

Line::Line(float x1, float y1, float x2, float y2, Color stroke)
        : stroke_(stroke), x2_(x2), y2_(y2) {
    x_ = x1;
    y_ = y1;
    IsVisible = true;
}

void Line::Render(int16_t display[320][480]) {
    if (!IsVisible)
        return;

    float vx = x2_ - x_;// vector x
    float vy = y2_ - y_;// vector y
    float length = (int) sqrt(vx * vx + vy * vy); // vector size

    for (int i = 0; i < length; ++i) {
        //compute coordinates for each point of the line
        int x = (int) (x_ + i * vx / length);
        int y = (int) (y_ + i * vy / length);

        //display owerflow control
        if (InsideDisplay(x, y))
            display[y][x] = (int16_t) stroke_.getRGB565();
    }
}

