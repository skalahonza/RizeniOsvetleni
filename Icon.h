//
// Created by skala on 23.5.17.
//

#ifndef UDPTASK_ICON_H
#define UDPTASK_ICON_H


#include "Shape.h"

class Icon : public Shape {
public:
    Icon(int x, int y, uint16_t pixels[256]);

    virtual void Render(uint16_t display[320][480]);

private:
    uint16_t icon_[256];
};


#endif //UDPTASK_ICON_H
