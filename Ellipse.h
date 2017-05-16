//
// Created by skala on 14.5.17.
//

#ifndef UDPTASK_ELLIPSE_H
#define UDPTASK_ELLIPSE_H


#include "Shape.h"

class Ellipse : public Shape {
public:
    Ellipse(float x, float y, int width, int height, Color Stroke);

    virtual void Render(int16_t display[320][480]);

private:
    int width_;
    int height_;
};


#endif //UDPTASK_ELLIPSE_H
