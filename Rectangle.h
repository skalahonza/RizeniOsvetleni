//
// Created by skala on 12.5.17.
//

#ifndef UDPTASK_RECTANGLE_H
#define UDPTASK_RECTANGLE_H


#include "Shape.h"
#include "Color.h"

class Rectangle : public Shape {
public:
    /**
     * Empty constructor for later initialization
     */
    Rectangle();

    /**
     * Creates 2D rectangle object, not filled
     * @param x1 Display coordinate
     * @param y1 Display coordinate
     * @param x2 Display coordinate
     * @param y2 Display coordinate
     * @param Stroke Line color
     */
    Rectangle(float x1, float y1, float x2, float y2, Color Stroke);

    /**
     * Creates 2D rectangle object, not filled
     * @param Stroke
     * @param x Display coordinate
     * @param y Display coordinate
     * @param width Width of the rectangle
     * @param height Height of the rectangle
     */
    Rectangle(Color Stroke, float x, float y, int width, int height);

    /**
     * Renders the object on target display
     * @param display Pointer to display 320x480
     */
    virtual void Render(uint16_t display[320][480]);

    float getX2_() const;

    void setX2_(float x2_);

    float getY2_() const;

    void setY2_(float y2_);

private:
    float x2_;
    float y2_;
};


#endif //UDPTASK_RECTANGLE_H
