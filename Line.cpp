//
// Created by skala on 12.5.17.
//

#include "Line.h"

unsigned short Line::getX2() const {
    return x2_;
}

unsigned short Line::getY2() const {
    return y2_;
}

Line::Line(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2) {
    x_ = x1;
    y_ = y1;
    x2_ = x2;
    y2_ = y2;
}

void Line::Render(char display[320][480]) {

}

