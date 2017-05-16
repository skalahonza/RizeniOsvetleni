//
// Created by skala on 14.5.17.
//

#ifndef UDPTASK_TEXTBOX_H
#define UDPTASK_TEXTBOX_H


#include "Shape.h"
#include <string>

class TextBox : public Shape {
public:
    TextBox(float x, float y, int width, int height, Color Stroke);

    int getWidth_() const;

    void setWidth_(int width_);

    int getHeight_() const;

    void setHeight_(int height_);

    const std::string &getText_() const;

    void setText_(const std::string &text_);

    virtual void Render(int16_t display[320][480]);

private:
    int width_;
    int height_;
    std::string text_;
};


#endif //UDPTASK_TEXTBOX_H
