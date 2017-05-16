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
    Color();
    Color(RGBcolor rgb888);

    Color(unsigned char r, unsigned char g, unsigned char b);

    RGBcolor getRGB888();

    int16_t getRGB565();

private:
    RGBcolor rgb888_;
    int16_t rgb565_;
};


#endif //UDPTASK_COLOR_H
