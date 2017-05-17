//
// Created by skala on 12.5.17.
//

#include "Shape.h"



int Shape::signum(int number) {
    return number > 0 ? 1 : (number < 0 ? -1 : 0);
}

void Shape::Show() {
    if (!IsVisible) IsVisible = true;
}

void Shape::Hide() {
    if (IsVisible) IsVisible = false;
}

bool Shape::InsideDisplay(int x, int y) {
    return ((x >= 0 && x < 480) && (y >= 0 && y < 320));
}

Shape::Shape(float x, float y, Color Stroke) : stroke_(Stroke), x_(x), y_(y) {
    IsVisible = true;
}

Shape::Shape(Color Stroke) : stroke_(Stroke) {
    IsVisible = true;
}

Shape::Shape() : Shape(Color()) {
}

float Shape::getX_() const {
    return x_;
}

void Shape::setX_(float x_) {
    Shape::x_ = x_;
}

float Shape::getY_() const {
    return y_;
}

void Shape::setY_(float y_) {
    Shape::y_ = y_;
}

const Color &Shape::getStroke_() const {
    return stroke_;
}

void Shape::setStroke_(const Color &stroke_) {
    Shape::stroke_ = stroke_;
}
