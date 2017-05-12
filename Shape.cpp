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

bool Shape::isIsVisible() const {
    return IsVisible;
}

void Shape::setX(float x_) {
    Shape::x_ = x_;
}

void Shape::setY(float y_) {
    Shape::y_ = y_;
}
