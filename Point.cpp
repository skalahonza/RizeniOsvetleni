//
// Created by skala on 12.5.17.
//

#include "Point.h"

Point::Point(float x, float y, Color stroke) : Shape(x, y, Color(stroke)) {
}

void Point::Render(uint16_t display[320][480]) {
    if (!IsVisible) return;
    display[(int) y_][(int) x_] = stroke_.getRGB565();
}

float Point::Getx() {
    return x_;
}

float Point::Gety() {
    return y_;
}

Point::Point() {

}
