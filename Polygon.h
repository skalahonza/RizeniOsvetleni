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
    Polygon();
    Polygon(std::vector<Point>, Color Stroke);

    virtual void Render(int16_t display[320][480]);

private:
    std::vector<Point> points_;

};


#endif //UDPTASK_POLYGON_H
