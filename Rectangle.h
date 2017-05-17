//
// Created by skala on 12.5.17.
//

#ifndef UDPTASK_RECTANGLE_H
#define UDPTASK_RECTANGLE_H


#include "Shape.h"
#include "Color.h"

class Rectangle : public Shape {
public:
    Rectangle();
    Rectangle(float x1, float y1, float x2, float y2, Color Stroke);

    Rectangle(Color Stroke, float x, float y, int width, int height);

    virtual void Render(int16_t display[320][480]);

    float getX2_() const;

    void setX2_(float x2_);

    float getY2_() const;

    void setY2_(float y2_);

private:
    float x2_;
    float y2_;
};


#endif //UDPTASK_RECTANGLE_H
