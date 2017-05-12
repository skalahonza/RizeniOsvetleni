//
// Created by skala on 12.5.17.
//

#include "Rectangle.h"

void Rectangle::Render(int16_t display[320][480]) {
    if (!IsVisible) return;


}

Rectangle::Rectangle(float x1, float y1, float x2, float y2, Color Stroke) : Shape(Color(Stroke)) {
    x_ = x1;
    y_ = y1;
    x2_ = x2;
    y2_ = y2;
}

