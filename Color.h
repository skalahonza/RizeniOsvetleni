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

    static Color black() { return Color(0, 0, 0); }

    static Color white() { return Color(255, 255, 255); }

    static Color red() { return Color(255, 0, 0); }

    static Color lime() { return Color(0, 255, 0); }

    static Color blue() { return Color(0, 0, 255); }

    static Color yellow() { return Color(255, 255, 0); }

    static Color cyan() { return Color(0, 255, 255); }

    static Color magenta() { return Color(255, 0, 255); }

    static Color silver() { return Color(192, 192, 192); }

    static Color gray() { return Color(128, 128, 128); }

    static Color maroon() { return Color(128, 0, 0); }

    static Color olive() { return Color(128, 128, 0); }

    static Color green() { return Color(0, 128, 0); }

    static Color purple() { return Color(128, 0, 128); }

    static Color teal() { return Color(0, 128, 128); }

    static Color navy() { Color(0, 0, 128); }

private:
    RGBcolor rgb888_;
    int16_t rgb565_;
};


#endif //UDPTASK_COLOR_H
