//
// Created by skala on 12.5.17.
//

#ifndef UDPTASK_POINT_H
#define UDPTASK_POINT_H


#include "Shape.h"
#include "Color.h"

class Point : public Shape {
public:
    Point(float x, float y, Color stroke);

    virtual void Render(int16_t display[320][480]);

private:
    Color stroke_;
};


#endif //UDPTASK_POINT_H
