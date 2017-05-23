//
// Created by skala on 12.5.17.
//

#include <iostream>
#include "Rectangle.h"
#include "Line.h"

void Rectangle::Render(uint16_t display[320][480]) {
    if (!IsVisible) return;

    Line a = Line(x_, y_, x2_, y_, stroke_);
    Line b = Line(x_, y_, x_, y2_, stroke_);
    Line c = Line(x_, y2_, x2_ + 1, y2_, stroke_);
    Line d = Line(x2_, y_, x2_, y2_, stroke_);

    a.Render(display);
    b.Render(display);
    c.Render(display);
    d.Render(display);
}

Rectangle::Rectangle(float x1, float y1, float x2, float y2, Color Stroke) : Shape(x1, y1, Color(Stroke)), x2_(x2),
                                                                             y2_(y2) {
}

Rectangle::Rectangle(Color Stroke, float x, float y, int width, int height) : Shape(x, y, Stroke) {
    x2_ = x + width;
    y2_ = y + height;
}

Rectangle::Rectangle() {

}

float Rectangle::getX2_() const {
    return x2_;
}

void Rectangle::setX2_(float x2_) {
    Rectangle::x2_ = x2_;
}

float Rectangle::getY2_() const {
    return y2_;
}

void Rectangle::setY2_(float y2_) {
    Rectangle::y2_ = y2_;
}

