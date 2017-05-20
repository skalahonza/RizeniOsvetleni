//
// Created by skala on 12.5.17.
//

#ifndef UDPTASK_COLOR_H
#define UDPTASK_COLOR_H


#include <sys/param.h>
#include <inttypes.h>
#include <string>

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

    Color(int r, int g, int b, std::string name);

    RGBcolor getRGB888() const;

    int16_t getRGB565();

    uint32_t toUINT32() const;

    static Color fromUINT32(uint32_t data);

    static Color black() { return Color(0, 0, 0, "BLACK"); }

    static Color white() { return Color(255, 255, 255, "WHITE"); }

    static Color red() { return Color(255, 0, 0, "RED"); }

    static Color lime() { return Color(0, 255, 0, "LIME"); }

    static Color blue() { return Color(0, 0, 255, "BLUE"); }

    static Color yellow() { return Color(255, 255, 0, "YELLOW"); }

    static Color cyan() { return Color(0, 255, 255, "CYAN"); }

    static Color magenta() { return Color(255, 0, 255, "MAGENTA"); }

    static Color silver() { return Color(192, 192, 192, "SILVER"); }

    static Color gray() { return Color(128, 128, 128, "GRAY"); }

    static Color maroon() { return Color(128, 0, 0, "MAROON"); }

    static Color olive() { return Color(128, 128, 0, "OLIVE"); }

    static Color green() { return Color(0, 128, 0, "GREEN"); }

    static Color purple() { return Color(128, 0, 128, "PURPLE"); }

    static Color teal() { return Color(0, 128, 128, "TEAL"); }

    static Color navy() { Color(0, 0, 128, "NAVY"); }

    const std::string &getName_() const;

private:
    RGBcolor rgb888_;
    std::string name_;
};


#endif //UDPTASK_COLOR_H
