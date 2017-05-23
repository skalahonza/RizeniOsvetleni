//
// Created by skala on 12.5.17.
//

#ifndef UDPTASK_POLYGON_H
#define UDPTASK_POLYGON_H


#include <vector>
#include "Shape.h"
#include "Point.h"

class Polygon : public Shape {
public:
    /**
     * Empty constructor for later initialization
     */
    Polygon();

    /**
     * Creates geometric polygon, not filled
     * @param Points All points of the polygon
     * @param Stroke Polygon line color
     */
    Polygon(std::vector<Point> Points, Color Stroke);

    /**
     * Renders the object on target display
     * @param display Pointer to display 320x480
     */
    virtual void Render(uint16_t display[320][480]);

private:
    std::vector<Point> points_;

};


#endif //UDPTASK_POLYGON_H
