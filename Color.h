//
// Created by skala on 12.5.17.
//

#ifndef UDPTASK_COLOR_H
#define UDPTASK_COLOR_H


#include <sys/param.h>
#include <inttypes.h>

typedef struct {
    int r;
    int g;
    int b;
} RGBcolor;


class Color {
public:
    Color();
    Color(RGBcolor rgb888);

    Color(int r, int g, int b);

    RGBcolor getRGB888() const;

    int16_t getRGB565();

    uint32_t toUINT32() const;

    static Color fromUINT32(uint32_t data);

private:
    RGBcolor rgb888_;
    int16_t rgb565_;
};


#endif //UDPTASK_COLOR_H
