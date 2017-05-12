//
// Created by skala on 12.5.17.
//

#include "Polygon.h"
#include "Line.h"

Polygon::Polygon(std::vector<Point> Points, Color Stroke) : Shape(Stroke), points_(Points) {
}

void Polygon::Render(int16_t display[320][480]) {
    if (!IsVisible) return;

    //draw lines that will form the polygon together
    for (int i = 0; i < points_.size(); ++i) {
        Point a = points_[i];
        Point b = points_[(i + 1) % points_.size()];
        Line line = Line(a.Getx(), a.Gety(), b.Getx(), b.Gety(), stroke_);
        line.Render(display);
    }
}
