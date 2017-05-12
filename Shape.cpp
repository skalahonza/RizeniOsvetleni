//
// Created by skala on 12.5.17.
//

#include "Shape.h"

unsigned short int Shape::GetX() const {
    return x_;
}

unsigned short int Shape::GetY() const {
    return y_;
}

int Shape::signum(int number) {
    return number > 0 ? 1 : (number < 0 ? -1 : 0);
}

void Shape::Show() {
    if (!IsVisible) IsVisible = true;
}

void Shape::Hide() {
    if (IsVisible) IsVisible = false;
}
