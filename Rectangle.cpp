//
// Created by skala on 12.5.17.
//

#include "Rectangle.h"

void Rectangle::Render(int16_t display[320][480]) {
    if (!IsVisible) return;


}

Rectangle::Rectangle(float x1, float y1, Color Stroke, float x2, float y2) : Shape(x1, y1, Color(Stroke)), x2_(x2),
                                                                             y2_(y2_) {
}

