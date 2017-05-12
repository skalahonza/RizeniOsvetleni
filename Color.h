//
// Created by skala on 12.5.17.
//

#ifndef UDPTASK_COLOR_H
#define UDPTASK_COLOR_H


#include <sys/param.h>

typedef struct {
    char r;
    char g;
    char b;
} RGBcolor;


class Color {
public:
    Color(RGBcolor rgb888);

    RGBcolor getRGB888();

    u_int16_t getRGB565();

private:
    RGBcolor rgb888_;
    u_int16_t rgb565_;
};


#endif //UDPTASK_COLOR_H
