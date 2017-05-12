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

float Shape::getX() const {
    return x_;
}

float Shape::getY() const {
    return y_;
}

void Shape::setX(float x_) {
    Shape::x_ = x_;
}

void Shape::setY(float y_) {
    Shape::y_ = y_;
}

bool Shape::InsideDisplay(int x, int y) {
    return ((x > 0 && x < 480) && (y > 0 && y < 320));
}
