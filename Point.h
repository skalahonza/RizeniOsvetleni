//
// Created by skala on 12.5.17.
//

#ifndef UDPTASK_POINT_H
#define UDPTASK_POINT_H


#include "Shape.h"
#include "Color.h"

class Point : public Shape {
public:
    /**
     * Empty constructor for later initialization
     */
    Point();

    /**
     * Geometric point - size of pixel
     * @param x display coordinate
     * @param y display coordinate
     * @param stroke point color
     */
    Point(float x, float y, Color stroke);

    float Getx();

    float Gety();

    /**
     * Renders the object on target display
     * @param display Pointer to display 320x480
     */
    virtual void Render(uint16_t display[320][480]);
};


#endif //UDPTASK_POINT_H
