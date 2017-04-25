//
// Created by Jan Skála on 25.04.2017.
//

#ifndef UDPTASK_DRAWER_H
#define UDPTASK_DRAWER_H


#include <basetsd.h>

class Drawer {
public:
    Drawer();
    ~Drawer();

private:
    UINT16 pixels[320][480];
};


#endif //UDPTASK_DRAWER_H
