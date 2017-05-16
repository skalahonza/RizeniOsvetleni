//
// Created by skala on 12.5.17.
//

#ifndef UDPTASK_LINE_H
#define UDPTASK_LINE_H


#include "Shape.h"
#include "Color.h"

class Line : public Shape {

public:
    Line(float x1, float y1, float x2, float y2, Color stroke);

    virtual void Render(int16_t display[320][480]);

    float getX2() const;

    float getY2() const;

private:
    float x2_;
    float y2_;
};


#endif //UDPTASK_LINE_H
