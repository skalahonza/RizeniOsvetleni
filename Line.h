//
// Created by skala on 12.5.17.
//

#ifndef UDPTASK_LINE_H
#define UDPTASK_LINE_H


#include "Shape.h"

class Line : public Shape {

public:
    Line(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2);

    virtual void Render(char display[320][480]);

    unsigned short getX2() const;

    unsigned short getY2() const;

private:
    unsigned short int x2_;
    unsigned short int y2_;
};


#endif //UDPTASK_LINE_H
