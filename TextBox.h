//
// Created by skala on 14.5.17.
//

#ifndef UDPTASK_TEXTBOX_H
#define UDPTASK_TEXTBOX_H


#include "Shape.h"
#include <string>

class TextBox : public Shape {
public:
    /**
     * Default constructor, for later initialization
     */
    TextBox();

    /**
     * Creates an instance of textbox on specified coordinates with max width and height
     * @param x coordinate on display
     * @param y coordinate on display
     * @param width used for text owvrflow check
     * @param height used for text wrapping
     * @param Stroke Font color
     */
    TextBox(float x, float y, int width, int height, Color Stroke);

    int getWidth_() const;

    void setWidth_(int width_);

    int getHeight_() const;

    void setHeight_(int height_);

    const std::string &getText_() const;

    /**
     * Sets the text that should be rendered on the textbox area
     * @param text_ UNICODE text, e.g. Hello world
     */
    void setText_(const std::string &text_);

    /**
     * Renders the object on target display
     * @param display Pointer to display 320x480
     */
    virtual void Render(int16_t display[320][480]);

private:
    int width_;
    int height_;
    std::string text_;
};


#endif //UDPTASK_TEXTBOX_H
