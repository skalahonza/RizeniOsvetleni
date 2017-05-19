//
// Created by skala on 14.5.17.
//

#ifndef UDPTASK_ELLIPSE_H
#define UDPTASK_ELLIPSE_H


#include "Shape.h"

class Ellipse : public Shape {
public:
    /**
     * Empty constructor for later initialization
     */
    Ellipse();

    /**
     * Creates Ellipse geometric object, filled
     * @param x Display coordinate, x of the center
     * @param y Display coordinate, y of the center
     * @param width Width of the ellipse (horizontal)
     * @param height Height of the ellipse (vertical)l
     * @param Stroke Color of the ellipse
     */
    Ellipse(float x, float y, int width, int height, Color Stroke);

    /**
     * Renders the object on target display
     * @param display Pointer to display 320x480
     */
    virtual void Render(int16_t display[320][480]);

private:
    int width_;
    int height_;
};


#endif //UDPTASK_ELLIPSE_H
